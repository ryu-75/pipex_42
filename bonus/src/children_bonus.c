/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:46:52 by nlorion           #+#    #+#             */
/*   Updated: 2022/10/10 15:26:16 by nlorion          ###   ########.fr       */
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
	else if (path && execve(path, mycmd, data->envp) == -1)
	{
		free_split(mycmd);
		free(path);
		ft_error("error");
	}
	else
		cmd_not_found(mycmd);
}

void	init_fd(t_pipex *data)
{
	if (data->av[1] && data->fd_in)
		open(data->av[1], O_RDONLY);
	else if (data->fd_in < 0)
		close(data->fd_in);
	else if (data->av[data->ac -1] && data->fd_out)
		open(data->av[data->ac - 1], O_WRONLY | O_CREAT |O_TRUNC, 0664);
	else if (data->fd_out < 0)
		ft_error("error");
}

void	child_process(t_pipex *data)
{
	int	pid;
	int	i;
	char	**mycmd;
	char	*path;
	
	i = 0;
	pid = fork();
	while (i++ < data->ac - 1)
	{
		if (pid < 0)
			ft_error("fork");
		else
		{
			mycmd = ft_split(data->av[2 + i], ' ');
			path = return_path(data, data->av[2 + i]);
			if (dup2(data->fd_in, STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
			else if (dup2(data->fd_dup[2 * i - 2], data->fd_out) == -1)
				exit(EXIT_FAILURE);
			else if (dup2(data->fd_dup[2 * i - 2], data->fd_dup[2 * i + 1]) == -1)
				exit(EXIT_FAILURE);
			exec_cmd(data, mycmd, path);
		}
	}
}