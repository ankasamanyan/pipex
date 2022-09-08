/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:57 by ankasamanya       #+#    #+#             */
/*   Updated: 2022/09/08 19:44:38 by akasaman         ###   ########.fr       */
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

char	*

int main(int argc, char const *argv[], char *env[])
{
	if (argc == 0)
		return 0;
	//find an executable in the path thingy 
	printf("%s\n", argv[0]); 

	// int i;
	
	// i = 1;
	// while (i++ <= argc - 2 )
	// {
	// 	//найти комманду в энвп
		
	// 	//сплит
		
	// }
	
	char *big_path = find_big_path(env);
	if (str)
		printf("%s\n",str);

	
	// while(*env)
	// 	printf("%s\n",*env++);
	return 0;
}
