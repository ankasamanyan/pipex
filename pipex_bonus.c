/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:03:33 by akasaman          #+#    #+#             */
/*   Updated: 2022/09/25 20:14:33 by akasaman         ###   ########.fr       */
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
	return (pipy[READ_PIPE]);
}

void	halp(t_vars *vars)
{
	if (vars->input_file < 0)
	{
		perror("Inputfile error");
		pipe(vars->pipe);
		close(vars->pipe[WRITE_PIPE]);
		vars->input_file = vars->pipe[READ_PIPE];
	}
	if (vars->output_file < 0)
	{
		perror("Output file error");
		exit(-1);
	}
}
