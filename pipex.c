/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:57 by ankasamanya       #+#    #+#             */
/*   Updated: 2022/09/09 16:11:44 by akasaman         ###   ########.fr       */
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

char	*find_lil_path(char *big_path, char *command, t_vars *vars)
{
	char	**smoll_pathsies;

	smoll_pathsies = ft_split(big_path, ':');
	vars->command = ft_split(command, ' ');
	while (*smoll_pathsies)
	{
		vars->full_path = ft_strjoin(*smoll_pathsies++, ft_strjoin("/", vars->command[0]));
		if (access( vars->full_path, F_OK) == 0)
			return (vars->full_path);
	}
	return (NULL); //???????
}

int main(int argc, char *argv[], char *env[])
{
	t_vars	vars;
	if (argc == 0)
		return 0;
	//find an executable in the path thingy 
	// printf("%s\n", argv[0]); 

	// int i;
	
	// i = 1;
	// while (i++ <= argc - 2 )
	// {
	// 	//найти комманду в энвп
		
	// 	//сплит
		
	// }
	
	char	*big_path;
	char	*lil_path;

	big_path = find_big_path(env);
		// printf("%s\n",big_path);
	lil_path = find_lil_path(big_path, argv[1], &vars);
	// if (lil_path)
		printf("\nthis would be the lil path: %s\n",lil_path);

	
	// while(*env)
	// 	printf("%s\n",*env++);
	return 0;
}
