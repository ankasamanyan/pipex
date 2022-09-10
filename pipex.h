/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankasamanyan <ankasamanyan@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:49 by ankasamanya       #+#    #+#             */
/*   Updated: 2022/09/10 16:11:15 by ankasamanya      ###   ########.fr       */
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
    char    **command;
	char	**env;
    char    *full_path;
    char    **argv;
    int     count;
	int		pipe[2];
	int		input_file;
	int		output_file;
	int		pid;
}   t_vars;

/* find paths */
char	*find_big_path(char	**env);
char	*find_lil_path(char *big_path, t_vars *vars);
/* command */
void	kiddi_process(t_vars *vars);

/* free stuff */
#endif