/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankasamanyan <ankasamanyan@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:03:33 by akasaman          #+#    #+#             */
/*   Updated: 2022/09/22 15:33:39 by ankasamanya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc_thingy(t_vars *vars)
{
	char	*stringy;
	int		pipy[2];

	pipe(pipy);
	while (1)
	{
		stringy = get_next_line(STDIN_FILENO);
		if ((ft_strncmp(stringy, vars->argv[2], ft_strlen(vars->argv[2])) == 0)
			&& (stringy[ft_strlen(vars->argv[2])] == '\n'))
			break ;
		else
			write(pipy[WRITE_PIPE], stringy, ft_strlen(stringy));
		free(stringy);
	}
	free(stringy);
	close(pipy[WRITE_PIPE]);
	// printf("apparently %s\n",get_next_line(pipy[READ_PIPE]));
	return (pipy[READ_PIPE]);
}
