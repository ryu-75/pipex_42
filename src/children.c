/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:46:52 by nlorion           #+#    #+#             */
/*   Updated: 2022/10/06 11:53:34 by nlorion          ###   ########.fr       */
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
	path = return_path(envp, av[2]);
	mycmd = ft_split(av[2], ' ');
	close(fd_dup[0]);
	if (dup2(fd, STDIN_FILENO < 0))
		exit(EXIT_FAILURE);
	close(fd);
	dup2(fd_dup[1], STDOUT_FILENO);
	close(fd_dup[1]);
	if (mycmd[0] && path)
	{
		if (execve(path, mycmd, envp) == -1)
		{
			free_split(mycmd);
			ft_error("error");
		}
	}
	else
		cmd_not_found(mycmd);
}

void	parent(char **av, int *fd_dup, char **envp)
{
	char	*path;
	char	**mycmd;
	int		fd;

	fd = creat(av[4], 0644);
	if (fd < 0)
		ft_error("error");
	path = return_path(envp, av[3]);
	mycmd = ft_split(av[3], ' ');
	close(fd_dup[1]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (dup2(fd_dup[0], STDIN_FILENO < 0))
		exit(EXIT_FAILURE);
	close(fd_dup[0]);
	if (mycmd[0] && path)
	{
		if (execve(path, mycmd, envp) == -1)
		{
			free_split(mycmd);
			ft_error("error");
		}
	}
	else
		cmd_not_found(mycmd);
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
