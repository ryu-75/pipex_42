/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:46:52 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/28 17:31:30 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child(char **av, int *fd_dup, char **envp)
{
	char	*path;
	char	**mycmd;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_error("error");
	else
	{
		path = return_path(envp, av[2]);
		mycmd = ft_split(av[2], ' ');
		close(fd_dup[0]);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(fd_dup[1], STDOUT_FILENO);
		close(fd_dup[1]);
		if (mycmd[0] && path)
		{
			execve(path, mycmd, envp);
			all_free(path, mycmd);
		}
		else
			cmd_not_found(path, mycmd);
	}
}

void	parent(char **av, int *fd_dup, char **envp)
{
	char	*path;
	char	**mycmd;
	int		fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_error("error");
	else
	{
		path = return_path(envp, av[3]);
		mycmd = ft_split(av[3], ' ');
		close(fd_dup[1]);
		dup2(fd, STDOUT_FILENO);
		dup2(fd_dup[0], STDIN_FILENO);
		close(fd_dup[0]);
		close(fd);
		if (mycmd[0] && path)
		{
			execve(path, mycmd, envp);
			all_free(path, mycmd);
		}
		else
			cmd_not_found(path, mycmd);
	}
}

void	pipex(char **av, int *fd_dup, char **envp)
{
	int	pid1;
	int	pid2;
	int	status;

	pid1 = fork();
	if (pid1 < 0)
		ft_error("fork");
	else if (pid1 == 0)
		child(av, fd_dup, envp);
	pid2 = fork();
	if (pid2 < 0)
		ft_error("fork");
	else if (pid2 == 0)
		parent(av, fd_dup, envp);
	close(fd_dup[0]);
	close(fd_dup[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}