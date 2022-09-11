/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:57 by ankasamanya       #+#    #+#             */
/*   Updated: 2022/09/11 19:32:37 by akasaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_big_path(char	**env)
{
	while (*env)
		if (ft_strncmp(*env++, "PATH=", 5) == 0)
			return (*(env - 1) + 5);
	return (NULL);
}

char	*find_lil_path(char *big_path, t_vars *vars)
{
	char	**smoll_pathsies;
	char	*lil_path;

	smoll_pathsies = ft_split(big_path, ':');
	while (*smoll_pathsies)
	{
		vars->command = ft_split(vars->argv[vars->index], ' '); // command cound has to be dinamic
		lil_path = ft_strjoin(*smoll_pathsies++, ft_strjoin("/", vars->command[0]));
		if (access( lil_path, X_OK) == 0)
			vars->full_path = lil_path;
	}
	while (*smoll_pathsies)
		free(*smoll_pathsies++);
	return (NULL); //???????
}


void	kiddi_process(t_vars *vars)
{
	dup2(vars->input_file, STDIN_FILENO);
	// if (vars->index == vars->argc - 3)
	dup2(vars->output_file, STDOUT_FILENO); //output rediraction 
	// else
	// 	dup2(vars->pipe[WRITE_PIPE], STDOUT_FILENO); //output rediraction
	// close(vars->pipe[READ_PIPE]);
	execve(vars->full_path, vars->command, vars->env);
}

void	init(t_vars *vars, int argc, char **argv, char **env)
{
	vars->argv = argv;
	vars->env = env;
	vars->argc = argc;
	vars->index = 0;
	vars->input_file = open(argv[1], O_RDONLY);
	vars->output_file = open(argv[argc], O_WRONLY | O_TRUNC | O_CREAT, 0777);
}

int main(int argc, char *argv[], char *env[])
{
	t_vars	vars;

	vars.count = 2; //временно
	init(&vars, argc, argv, env);
	if (argc == 0)
		return 0;
	while (vars.index++ <= argc - 2)
	{
		printf("%i\n", vars.index);
		// printf("%i\n", argc);
		pipe(vars.pipe); 
		find_lil_path(find_big_path(env), &vars);
		vars.pid = fork();
		if (vars.pid == 0)
		{
			kiddi_process(&vars);
		}
		else
		{
			close(vars.pipe[WRITE_PIPE]);
			wait(0);
		}
	}
	return 0;
}
