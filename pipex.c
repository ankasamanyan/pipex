/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankasamanyan <ankasamanyan@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:08:26 by akasaman          #+#    #+#             */
/*   Updated: 2022/09/24 23:45:14 by ankasamanya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init(t_vars *vars, int argc, char **argv, char **env)
{
	vars->argv = argv;
	vars->env = env;
	vars->argc = argc;
	vars->index = 1;
	vars->here_doc = 0;
	vars->temp_pipe = 1;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		vars->here_doc = 1;
		vars->index = 2;
		vars->input_file = here_doc_thingy(vars);
		vars->output_file = open(argv[argc - 1],
				O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	else
	{
		vars->input_file = open(argv[1], O_RDONLY);
		vars->output_file = open(argv[argc - 1],
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	halp(vars);
}

void	find_lil_path(char *big_path, t_vars *vars)
{
	char	**smoll_pathsies;
	char	*lil_path;
	int		i;

	i = 0;
	smoll_pathsies = ft_split(big_path, ':');
	vars->command = ft_split(vars->argv[vars->index], ' ');
	vars->full_path = NULL;
	while (smoll_pathsies[i])
	{
		lil_path = ft_triple_strjoin(smoll_pathsies[i++],
				"/", vars->command[0]);
		if (access(lil_path, X_OK) == 0)
			vars->full_path = lil_path;
		else
		{
			access(lil_path, F_OK);
			free(lil_path);
		}
	}
	if (access(vars->command[0], X_OK) == 0)
		vars->full_path = ft_strdup(vars->command[0]);
	else
		access(vars->command[0], F_OK);
	ft_free_array(smoll_pathsies);
}

void	kiddi_process(t_vars *vars)
{
	if (vars->here_doc == 0)
	{
		if (vars->index == 2)
			dup2(vars->input_file, STDIN_FILENO);
		else
			dup2(vars->temp_pipe, STDIN_FILENO);
	}
	else if (vars->here_doc != 0)
	{
		if (vars->index == 3)
			dup2(vars->input_file, STDIN_FILENO);
		else
			dup2(vars->temp_pipe, STDIN_FILENO);
	}
	if (vars->index == vars->argc - 2)
		dup2(vars->output_file, STDOUT_FILENO);
	else
		dup2(vars->pipe[WRITE_PIPE], STDOUT_FILENO);
	close(vars->pipe[READ_PIPE]);
	execve(vars->full_path, vars->command, vars->env);
	perror("execve error");
	exit(-1);
}

void	pipex(t_vars *vars)
{
	while (vars->index++ <= vars->argc - 3)
	{
		pipe(vars->pipe);
		find_lil_path(vars->big_path, vars);
		if (vars->full_path == NULL)
		{
			perror(vars->argv[vars->index]);
			vars->temp_pipe = vars->pipe[READ_PIPE];
			close(vars->pipe[WRITE_PIPE]);
			continue ;
		}
		vars->pid = fork();
		if (vars->pid == 0)
			kiddi_process(vars);
		else
		{
			waitpid(-1, NULL, WNOHANG);
			if (vars->temp_pipe != 1)
				close(vars->temp_pipe);
			vars->temp_pipe = vars->pipe[READ_PIPE];
			close(vars->pipe[WRITE_PIPE]);
			ft_free_array(vars->command);
			free(vars->full_path);
		}
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_vars	vars;

	if (argc < 5)
	{
		write(2, "Error: wrong number of arguments", 33);
		return (0);
	}
	init(&vars, argc, argv, env);
	while (*env)
		if (ft_strncmp(*env++, "PATH=", 5) == 0)
			vars.big_path = (*(env - 1) + 5);
	pipex(&vars);
	close(vars.input_file);
	close(vars.output_file);
	close(vars.temp_pipe);
	return (0);
}
