/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:57 by ankasamanya       #+#    #+#             */
/*   Updated: 2022/09/09 18:03:22 by akasaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_big_path(char	**env)
{
	while (*env)
		if (ft_strncmp(*env++, "PATH=", 5) == 0)
			return (*(env - 1) + 5);
	return (NULL); //???????
}

char	*find_lil_path(char *big_path, t_vars *vars)
{
	char	**smoll_pathsies;
	char	*lil_path;

	smoll_pathsies = ft_split(big_path, ':');
	while (*smoll_pathsies)
	{
		lil_path = ft_strjoin(*smoll_pathsies++, ft_strjoin("/", vars->command[0]));
		if (access( lil_path, F_OK) == 0)
			vars->full_path = lil_path;
	}
	// while (*smoll_pathsies)
	// 	free(*smoll_pathsies++);
	return (NULL); //???????
}

void	execute_command(t_vars *vars, char **env)
{
	vars->command = ft_split(vars->argv[vars->count], ' ');
	execve(vars->full_path, vars->command, env);
	printf("halp");
}

int main(int argc, char *argv[], char *env[])
{
	t_vars	vars;
	// char	*big_path;
	vars.argv = argv;
	vars.count = 1; //временно
	if (argc == 0)
		return 0;
	// printf("%s\n", argv[0]);
	
	// big_path = find_big_path(env);
	find_lil_path(find_big_path(env), &vars);
	//execute da thingy
	execute_command(&vars, env);
	if (vars.full_path)
		printf("\nthis would be the lil path: %s\n",vars.full_path);

	// int i;
	
	// i = 1;
	// while (i++ <= argc - 2 )
	// {
	// 	//найти комманду в энвп
		
	// 	//сплит
		
	// }
	
	// while(*env)
	// 	printf("%s\n",*env++);
	return 0;
}
