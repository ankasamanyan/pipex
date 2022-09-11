/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:49 by ankasamanya       #+#    #+#             */
/*   Updated: 2022/09/11 18:26:35 by akasaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "Libft/libft.h"
# include <fcntl.h>

# define READ_PIPE 0
# define WRITE_PIPE 1

typedef struct s_vars
{
    char    **argv;
	char	**env;
    char    **command;
    char    *full_path;
	int		argc;
    int     count;
	int		pipe[2];
	int		input_file;
	int		output_file;
	int		index;
	int		pid;
}   t_vars;

/* initialization */
void	init(t_vars *vars, int argc, char **argv, char **env);
/* find paths */
char	*find_big_path(char	**env);
char	*find_lil_path(char *big_path, t_vars *vars);
/* command */
void	kiddi_process(t_vars *vars);

/* free stuff */
#endif