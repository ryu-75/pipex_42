/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:55:43 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/15 17:18:36 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(int ac, char **av, char **envp)
{
    int fd_dup[2];
    int status;
    pid_t   pid;

    pid = fork();
    if (ac < 5)
    {
        write (2, "Expected : file1 [cmd1] [cmd2] file2\n", 37);
        exit(0);
    }
    else
    {
        if (pipe(fd_dup) < 0)
            ft_error("pipe");
        else
        {
            first_child(av, fd_dup, av[2], envp);
            second_child(av, fd_dup, av[3], envp);
        }
        close(fd_dup[0]);
        close(fd_dup[1]);
        waitpid(-1, &status, 0);
        waitpid(-1, &status, 0);
    }
    return (0);
}