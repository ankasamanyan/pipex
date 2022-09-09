/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankasamanyan <ankasamanyan@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:57 by ankasamanya       #+#    #+#             */
/*   Updated: 2022/09/09 09:07:14 by ankasamanya      ###   ########.fr       */
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

char	*find_lil_path(char *big_path, char *command)
{
	char	**smoll_pathsies;
	char	*lil_path;
	int		i;

	i = 0;
	smoll_pathsies = ft_split(big_path, ':');
	while (smoll_pathsies[i])
	{
		lil_path = ft_strjoin(smoll_pathsies[i], ft_strjoin("/", command));
		// printf("\n%s\n\n", lil_path);
		if (access( lil_path, F_OK) == 1)
		{
			printf("Halp");
			return (lil_path);
		}
		i++;
	}
	return (NULL); //???????
}

int main(int argc, char *argv[], char *env[])
{
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
		printf("%s\n",big_path);
	lil_path = find_lil_path(big_path, argv[1]);
	if (lil_path)
		printf("\nthis would be the lil path: %s\n",lil_path);

	
	// while(*env)
	// 	printf("%s\n",*env++);
	return 0;
}
