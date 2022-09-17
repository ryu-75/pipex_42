/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:31:47 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/17 14:07:14 by nlorion          ###   ########.fr       */
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

void	ft_error(char *s, char **cmd, char *path);
void	free_split(char **str);
void	cmd_not_found(char **cmd);
void	all_free(char *path, char **cmd);

//  ---------------------- [PIPEX] ------------------------------- //

void	first_child(char **av, int *fd_dup, char *cmd, char **envp);
void	second_child(char **av, int *fd_dup, char *cmd, char **envp);
#endif
