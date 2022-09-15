/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:46:52 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/15 22:57:29 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void    fd_setting(char *path, int *fd_dup, char **cmd, char **envp, int pid, int fd)
{
    if (pid == 0)
    {
        if (dup2(fd, STDIN_FILENO) < 0)
            ft_error("Error");
        dup2(fd_dup[1], STDOUT_FILENO);
        if (cmd && path)
            execve(path, cmd, envp);
        else 
            cmd_not_found(*cmd);  
    }
    else if (pid > 0)
    {
        dup2(fd_dup[0], STDIN_FILENO);
        if (dup2(fd, STDOUT_FILENO) < 0)
            ft_error("Error");
        if (cmd && path)
            execve(path, cmd, envp);
        else 
            cmd_not_found(*cmd); 
    }
}

void    first_child(char **av, int *fd_dup, char *cmd, char **envp)
{
    char    *path;
    char    **mycmd;
    pid_t   pid;
    int fd;
    
    pid = fork();
    path = return_path(envp, cmd);
    mycmd = ft_split(cmd, ' ');
    if (pid < 0)
        ft_error("fork");
    else if (pid == 0)
    {
        fd = open(av[1], O_RDONLY);
        if (fd < 0)
        {
            ft_error("Error");
            exit(0);
        }
        close(fd_dup[0]);
        fd_setting(path, fd_dup, mycmd, envp, pid, fd);
    }
    free_split(mycmd);
}

void    second_child(char **av, int *fd_dup, char *cmd, char **envp)
{
    char    *path;
    char    **mycmd;
    pid_t   pid;
    int fd;
    
    pid = fork();
    path = return_path(envp, cmd);
    mycmd = ft_split(cmd, ' ');
    if (pid < 0)
        ft_error("fork");
    else if (pid > 0)
    {
        fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            ft_error("Error");
            exit(0);
        }
        close(fd_dup[1]);
        fd_setting(path, fd_dup, mycmd, envp, pid, fd);
    }
    free_split(mycmd);
}