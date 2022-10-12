/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:46:52 by nlorion           #+#    #+#             */
/*   Updated: 2022/10/12 15:50:12 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec_cmd(t_pipex *data, char *cmd)
{
	char	*path;
	char	**mycmd;
	
	mycmd = ft_split(cmd, ' ');
	if (ft_strnstr(mycmd[0], "/", ft_strlen(mycmd[0])))
		path = mycmd[0];
	else
		path = return_path(data, cmd);
	if (execve(path, mycmd, data->envp) == -1)
	{
		free_split(mycmd);
		ft_error("error");
	} 
	else
		cmd_not_found(mycmd);
}

void	ft_process(t_pipex *data, char *cmd)
{
	pid_t	pid;
	int	status;
	
	if (pipe(data->fd_dup) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			ft_error("fork");
		if (pid)
		{
			close(data->fd_dup[0]);
			if (dup2(data->fd_dup[1], STDOUT_FILENO) < 0)
				exit(EXIT_FAILURE);
			close(data->fd_dup[1]);
			waitpid(pid, &status, 0);
		}
		else
		{
			close(data->fd_dup[1]);
			dup2(data->fd_dup[0], STDIN_FILENO);
			close(data->fd_dup[0]);
			if (data->fd_in < 0)
				ft_error("error");
			exec_cmd(data, cmd);
		}
	}	
}