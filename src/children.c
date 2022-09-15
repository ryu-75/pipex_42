/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:46:52 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/15 17:38:00 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void    first_child(char **av, int *fd_dup, char *cmd, char **envp)
{
    char    *path;
    char    **mycmd;
    pid_t   pid;
    int fd;
    
    pid = fork();
    path = return_path(envp, cmd, av[2]);
    if (pid < 0)
        ft_error("fork");
    else if (pid == 0)
    {
        printf("%d\n", pid);
        fd = open(av[1], O_RDONLY);
        if (fd < 0)
        {
            ft_error("Error");
            exit(0);
        }
        close(fd_dup[0]);
        if (dup2(fd, STDIN_FILENO) < 0)
            ft_error("Error");
        dup2(fd_dup[1], STDOUT_FILENO);
        mycmd = ft_split(cmd, ' ');
        if (cmd && path)
            execve(path, mycmd, envp);
        close(fd);
    }
}

void    second_child(char **av, int *fd_dup, char *cmd, char **envp)
{
    char    *path;
    char    **mycmd;
    pid_t   pid;
    int fd;
    
    pid = fork();
    path = return_path(envp, cmd, av[3]);
    if (pid < 0)
        ft_error("fork");
    else if (pid > 0)
    {
        printf("%d\n", pid);
        printf("OK\n");
        fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            ft_error("Error");
            exit(0);
        }
        close(fd_dup[1]);
        dup2(fd_dup[0], STDIN_FILENO);
        if (dup2(fd, STDOUT_FILENO) < 0)
            ft_error("Error");
        mycmd = ft_split(cmd, ' ');
        if (cmd && path)
            execve(path, mycmd, envp);
        close(fd);
    }
}