/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:31:47 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/05 17:31:47 by nlorion          ###   ########.fr       */
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

char    *return_path(char **envp, char *cmd, char **av);
char    **get_path(char **envp);

// ----------------------- [UTILS] ------------------------------- //

int ft_error(char *s);
void    free_split(char **str);
char    *cmd_not_found(char **cmd);

//  ---------------------- [PIPEX] ------------------------------- //

// void    first_child(char **av, int *fd_dup, int  *fd, char **envp);
int first_child(char **av, int *fd_dup, char *cmd, char **envp);
int second_child(char **av, int *fd_dup, char *cmd, char **envp);

// void    second_child(char **av, int *fd_dup, int *fd, char **envp);

# endif