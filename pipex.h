/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:49 by ankasamanya       #+#    #+#             */
/*   Updated: 2022/09/09 18:01:52 by akasaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "Libft/libft.h"

typedef struct s_vars
{
    char    **command;
    char    *full_path;
    char    **argv;
    int     count;
}   t_vars;
/* find paths */
char	*find_big_path(char	**env);
char	*find_lil_path(char *big_path, t_vars *vars);
/* command */
void	execute_command(t_vars *vars, char **env);
/* free stuff */
#endif