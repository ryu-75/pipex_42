/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:46:52 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/26 01:21:33 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	execute(char **cmd, char *path, char **envp, int fd)
{
	
	if (!(cmd[0] && path))
	{
		close(fd);
		cmd_not_found(cmd);
		all_free(path, cmd);
		exit(0);
	}
	else
	{
		execve(path, cmd, envp);
		free_split(cmd);
	}
}

static void	fd_setting(int *fd_dup, int fd, int pid)
{
	if (pid == 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
			exit(0);
		dup2(fd_dup[1], STDOUT_FILENO);
	}
	else if (pid > 0)
	{
		dup2(fd, STDOUT_FILENO);
		if (dup2(fd_dup[0], STDIN_FILENO) < 0)
			exit(0);
	}
}

void	first_child(char **av, int *fd_dup, char *cmd, char **envp)
{
	char	*path;
	char	**mycmd;
	pid_t	pid;
	int		fd;
	
	pid = fork();
	if (pid < 0)
		ft_error("fork");
	else if (pid == 0)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
			ft_error("error");
		path = return_path(envp, cmd);
		mycmd = ft_split(cmd, ' ');
		close(fd_dup[0]);
		fd_setting(fd_dup, fd, pid);
		execute(mycmd, path, envp, fd);
	}
}

void	second_child(char **av, int *fd_dup, char *cmd, char **envp)
{
	char	*path;
	char	**mycmd;
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid < 0)
		ft_error("fork");
	else if (pid > 0)
	{
		fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			ft_error("error");
		path = return_path(envp, cmd);
		mycmd = ft_split(cmd, ' ');
		close(fd_dup[1]);
		fd_setting(fd_dup, fd, pid);
		execute(mycmd, path, envp, fd);
		free_split(mycmd);
	}
}