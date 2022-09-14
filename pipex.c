/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankasamanyan <ankasamanyan@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:57 by ankasamanya       #+#    #+#             */
/*   Updated: 2022/09/14 11:15:24 by ankasamanya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init(t_vars *vars, int argc, char **argv, char **env)
{
	vars->argv = argv;
	vars->env = env;
	vars->argc = argc;
	vars->index = 1;
	vars->input_file = open(argv[1], O_RDONLY);
	vars->output_file = open(argv[argc - 1],
			O_WRONLY | O_TRUNC | O_CREAT, 0777);
}

char	*find_lil_path(char *big_path, t_vars *vars)
{
	char	**smoll_pathsies;
	char	*lil_path;
	int		i;

	i = 0;
	smoll_pathsies = ft_split(big_path, ':');
	while (smoll_pathsies[i])
	{
		vars->command = ft_split(vars->argv[vars->index], ' ');
		lil_path = ft_strjoin(smoll_pathsies[i++],
				ft_strjoin("/", vars->command[0]));
		if (access(lil_path, X_OK) == 0)
			vars->full_path = lil_path;
	}
	free_array(smoll_pathsies);
	return (NULL);
}

void	kiddi_process(t_vars *vars)
{
	if (vars->index == 2)
		dup2(vars->input_file, STDIN_FILENO);
	else
		dup2(vars->temp_pipe, STDIN_FILENO);
	if (vars->index == vars->argc - 2)
		dup2(vars->output_file, STDOUT_FILENO);
	else
		dup2(vars->pipe[WRITE_PIPE], STDOUT_FILENO);
	close(vars->pipe[READ_PIPE]);
	execve(vars->full_path, vars->command, vars->env);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
			free(array[i]);
		free(array);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_vars	vars;

	init(&vars, argc, argv, env);
	while (*env)
		if (ft_strncmp(*env++, "PATH=", 5) == 0)
		vars.big_path = (*(env - 1) + 5);
	if (argc == 0)
		return (0);
	while (vars.index++ <= argc - 3)
	{	
		pipe(vars.pipe);
		find_lil_path(vars.big_path, &vars);
		vars.pid = fork();
		if (vars.pid == 0)
			kiddi_process(&vars);
		else
		{
			waitpid(-1, NULL, WNOHANG);
			vars.temp_pipe = vars.pipe[READ_PIPE];
			free_array(vars.command);
			free(vars.full_path);
		}
	}
	return (0);
}
