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

// ----------------------- [PARSING] ----------------------------- //

char	*return_path(char **envp, char *cmd);
char	**get_path(char **envp);

// ----------------------- [UTILS] ------------------------------- //

void	ft_error(char *s);
void	free_split(char **str);
void	cmd_not_found(char **cmd);
// void	all_free(char *path, char **cmd);
int		check_access(char *mycmd, char **mycmdarg, char **paths, int type);

//  ---------------------- [PIPEX] ------------------------------- //

void	child(char **av, int *fd_dup, char **envp);
void	parent(char **av, int *fd_dup, char **envp);
void	pipex(char **av, int *fd_dup, char **envp);
#endif
