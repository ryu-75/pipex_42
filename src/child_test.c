/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:46:52 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/14 15:42:48 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int first_child(char **av, int *fd_dup, char *cmd, char **envp)
{
    int fd[2];
    char    *path;
    pid_t   pid;

    path = return_path(envp, &cmd[1], &av[2]);
    pid = fork();
    if (pid < 0)
        ft_error("fork");
    else if (pid == 0)
    {
        close(fd[1]);
        // if (!access(av[1], R_OK))
        //     ft_error("Error");
        fd[0] = open(av[1], O_RDONLY);
        if (fd[0] < 0)
        {
            ft_error("Error");
            exit(0);
        }
        close(fd_dup[0]);
        if (dup2(fd[0], STDIN_FILENO) < 0)
            return (EXIT_FAILURE);
        dup2(fd_dup[1], STDOUT_FILENO);
        if (cmd && path)
            execve(path, &av[2], envp);
        return (EXIT_SUCCESS);
    }
    return (0);
}

int second_child(char **av, int *fd_dup, char *cmd, char **envp)
{
    int fd[2];
    char    *path;
    pid_t   pid;

    path = return_path(envp, &cmd[4], &av[3]);
    pid = fork();
    if (pid < 0)
        ft_error("fork");
    else if (pid == 0)
    {
        close(fd[0]);
        // if (!access(av[4], W_OK))
        //     ft_error("Error");
        fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd[1] < 0)
        {
            ft_error("Error");
            exit(0);
        }
        close(fd_dup[1]);
        dup2(fd_dup[0], STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        if (cmd && path)
            execve(path, &av[3], envp);
        return (EXIT_SUCCESS);
    }
    return (0);
}