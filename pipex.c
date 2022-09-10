/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankasamanyan <ankasamanyan@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:57 by ankasamanya       #+#    #+#             */
/*   Updated: 2022/09/10 17:51:52 by ankasamanya      ###   ########.fr       */
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
		vars->command = ft_split(vars->argv[vars->count], ' ');
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
	// dup2(vars->pipe[WRITE_PIPE], STDOUT_FILENO); //output rediraction 
	close(vars->pipe[READ_PIPE]);
	//execute da thingy in da fork();
	execve(vars->full_path, vars->command, vars->env);
}

int main(int argc, char *argv[], char *env[])
{
	t_vars	vars;
	// char	*big_path;
	vars.argv = argv;
	vars.env = env;
	vars.count = 2; //временно
	if (argc == 0)
		return 0;
	// printf("%s\n", argv[0]);
	
	// printf("\nthis would be the lil path: %s\n",vars.full_path);
	
	// if (vars.full_path)
	// 	printf("\nthis would be the lil path: %s\n",vars.full_path);
	vars.input_file = open(argv[1], O_RDONLY);
	vars.output_file = open("file2.txt", O_WRONLY, O_TRUNC, O_CREAT, 777);
	
	int i;
	
	i = 1;
	while (i++ <= argc - 2 )
	{
		pipe(vars.pipe); 
		find_lil_path(find_big_path(env), &vars);
		vars.pid = fork();
		if (vars.pid == 0)
			kiddi_process(&vars);
		else
		{
			close(vars.pipe[WRITE_PIPE]);
			wait(0);
		}
	}
	
	// while(*env)
	// 	printf("%s\n",*env++);
	return 0;
}
