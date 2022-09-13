/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:23:22 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/08 14:23:22 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void    first_child(char **av, int *fd_dup, int *fd, char **envp)
{
    pid_t   our_pid;
    char    **cmd;

    our_pid = fork();
    if (our_pid < 0)
        ft_error("fork");
    else if (our_pid == 0)
    {
        fd[0] = open(av[1], O_RDONLY);
        if (fd[0] < 0)
            return (exit(0));
        cmd = ft_split(av[2], ' ');
        close(fd_dup[0]);
        dup2(fd[0], STDIN_FILENO);
        dup2(fd_dup[1], STDOUT_FILENO);
        if (cmd[0] && return_path(envp, cmd[0]))
        {
            execve(return_path(envp, cmd[0]), cmd, envp);
            free_split(cmd);
        }
        else 
            cmd_not_found(cmd);
    }
}

void    second_child(char **av, int *fd_dup, int *fd, char **envp)
{
    pid_t   our_pid;
    char    **cmd;

    our_pid = fork();
    if (our_pid < 0)
        ft_error("fork");
    else if (our_pid == 0)
    {
        fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd[1] < 0)
            return (exit(0));
        cmd = ft_split(av[3], ' ');
        close(fd_dup[1]);
        dup2(fd[1], STDOUT_FILENO);
        dup2(fd_dup[0], STDIN_FILENO);
        if (cmd[0] && return_path(envp, cmd[0]))
        {
            execve(return_path(envp, cmd[0]), cmd, envp);
            free_split(cmd);
        }
        else 
            cmd_not_found(cmd);
    }
}