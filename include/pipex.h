/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:31:47 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/27 11:57:09 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include  <errno.h>
# include <fcntl.h>

typedef struct s_pipex
{
    int fd;
    int ac;
    int fd_dup[2];
    char    *part_path;
    char    *mycmd;
    char    **mycmds;
    char    *cmd;
    char    **av;
    char    **paths;
    char    *path;
    char    **mycmdarg;
    char    **split_path;
}           t_pipex;


// ----------------------- [PARSING] ----------------------------- //

char	*return_path(t_pipex *data, char *cmd, char **envp);

// ----------------------- [UTILS] ------------------------------- //

void	ft_error(char *s);
void	free_split(char **str);
void	cmd_not_found(char **cmd);
int		check_access(char *mycmd, char **mycmdarg, char **paths, int type);
void	init_value(t_pipex *data, char **av, int ac);
void	ft_close_parent(t_pipex *data);
//  ---------------------- [PIPEX] ------------------------------- //

void	child(t_pipex *data, char **envp);
void	parent(t_pipex *data, char **envp);
void	pipex(t_pipex *data, char **envp);
#endif
