/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:46:52 by nlorion           #+#    #+#             */
/*   Updated: 2022/10/12 16:19:20 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	exec_cmd(t_pipex *data, char **mycmd, char *path)
{
	if (ft_strnstr(mycmd[0], "/", ft_strlen(mycmd[0]))
		&& execve(mycmd[0], mycmd, data->envp) == -1)
	{
		free_split(mycmd);
		free(path);
		ft_error("error");
	}
	else if (execve(path, mycmd, data->envp) == -1)
	{
		free_split(mycmd);
		free(path);
		ft_error("error");
	}
	else
		cmd_not_found(mycmd);
}

void	child(t_pipex *data)
{
	char	*path;
	char	**mycmd;

	data->fd = open(data->av[1], O_RDONLY);
	if (data->fd < 0)
		ft_error("error");
	path = return_path(data, data->av[2]);
	mycmd = ft_split(data->av[2], ' ');
	close(data->fd_dup[0]);
	if (dup2(data->fd, STDIN_FILENO < 0))
		exit(EXIT_FAILURE);
	close(data->fd);
	dup2(data->fd_dup[1], STDOUT_FILENO);
	close(data->fd_dup[1]);
	exec_cmd(data, mycmd, path);
}

void	parent(t_pipex *data)
{
	char	*path;
	char	**mycmd;
	
	data->fd = open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (data->fd < 0)
		ft_error("error");	
	path = return_path(data, data->av[3]);
	mycmd = ft_split(data->av[3], ' ');
	close(data->fd_dup[1]);
	dup2(data->fd, STDOUT_FILENO);
	close(data->fd);
	if (dup2(data->fd_dup[0], STDIN_FILENO < 0))
		exit(EXIT_FAILURE);
	close(data->fd_dup[0]);
	exec_cmd(data, mycmd, path);
}

void	pipex(t_pipex *data)
{
	pid_t	pid1;
	pid_t	pid2;
	int	status;

	pid1 = fork();
	if (pid1 < 0)
		ft_error("fork");
	else if (pid1 == 0)
		child(data);
	pid2 = fork();
	if (pid2 < 0)
		ft_error("fork");
	else if (pid2 == 0)
		parent(data);
	close(data->fd_dup[0]);
	close(data->fd_dup[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}