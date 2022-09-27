/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:46:52 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/27 18:33:26 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	execute(char **cmd, char *path, char **envp)
{
	if (!(cmd[0] && path))
	{
		cmd_not_found(cmd);
		all_free(path, cmd);
		exit(0);
	}
	else
	{
		execve(path, cmd, envp);
		all_free(path, cmd);
	}
}

static void	fd_setting_1(int *fd_dup, int fd)
{
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	dup2(fd_dup[1], STDOUT_FILENO);
	close(fd_dup[1]);
}

static void	fd_setting_2(int *fd_dup, int fd)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (dup2(fd_dup[0], STDIN_FILENO) < 0)
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd_dup[0]);
}

void	first_child(char **av, int *fd_dup, int *fd, char *cmd, char **envp)
{
	char	*path;
	char	**mycmd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork");
	else if (pid == 0)
	{
		fd[0] = open(av[1], O_RDONLY);
		if (fd[0] < 0)
			ft_error("error");
		path = return_path(envp, cmd);
		mycmd = ft_split(cmd, ' ');
		close(fd_dup[0]);
		fd_setting_1(fd_dup, fd[0]);
		execute(mycmd, path, envp);
	}
}

void	second_child(char **av, int *fd_dup, int *fd, char *cmd, char **envp)
{
	char	*path;
	char	**mycmd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork");
	else if (pid == 0)
	{
		fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] < 0)
			ft_error("error");
		path = return_path(envp, cmd);
		mycmd = ft_split(cmd, ' ');
		close(fd_dup[1]);
		fd_setting_2(fd_dup, fd[1]);
		execute(mycmd, path, envp);
	}
}