/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:55:43 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/14 15:27:53 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(int ac, char **av, char **envp)
{
    int fd[2];
    int fd_dup[2];
    int status;

    if (ac < 5)
        return (-1);
    else
    {
        if (pipe(fd_dup) < 0)
            ft_error("pipe");
        fd[0] = first_child(av, fd_dup, av[2], envp);
        fd[1] = second_child(av, fd_dup, av[3], envp);
        close(fd[0]);
        close(fd[1]);
        waitpid(-1, &status, 0);
        waitpid(-1, &status, 0);
    }
    return (0);
}