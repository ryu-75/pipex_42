/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:30:35 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/05 17:30:35 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// int main(int ac, char **av, char **envp)
// {
//     int fd[2];
//     int fd_dup[2];
//     int status;

//     errno = 0;
//     status = 1;
//     if (ac < 5)
//     {
//         write (2, "Usage : file1 cmd1 cmd2 file2\n", 30);
//         return (-1);
//     }
//     if (pipe(fd_dup) < 0)
//         ft_error("pipe");
//     first_child(av, fd_dup, fd, envp);
//     second_child(av, fd_dup, fd, envp);
//     close(fd_dup[0]);
//     close(fd_dup[1]);
//     waitpid(-1, &status, 0);
//     waitpid(-1, &status, 0);
//     return (0);
// }