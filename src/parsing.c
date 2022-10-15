/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:44:39 by nlorion           #+#    #+#             */
/*   Updated: 2022/10/15 14:34:47 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* We truncate the unix command with path,
it's allow to applicate the command on it */

static char	**get_env(t_pipex *data)
{
	int		i;
	char	**split_path;

	i = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], "PATH=", 5) != 0)
		i++;
	split_path = ft_split(data->envp[i] + 5, ':');
	return (split_path);
}

static char	*check_cmd(t_pipex *data, char *cmd)
{
	if (!*data->envp)
	{
		if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
			return (cmd);
		else
		{
			write(2, cmd, ft_strlen(cmd));
			ft_putstr_fd(": command not found\n", 2);
		}
	}
	return (NULL);
}

char	*return_path(t_pipex *data, char *cmd)
{	
	int	i;

	i = -1;
	check_cmd(data, cmd);
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	data->paths = get_env(data);
	data->mycmdarg = ft_split(cmd, ' ');
	while (data->paths[++i])
	{
		data->part_path = ft_strjoin(data->paths[i], "/");
		data->mycmd = ft_strjoin(data->part_path, *data->mycmdarg);
		free(data->part_path);
		if (access(data->mycmd, F_OK) == 0)
			return (data->mycmd);
		free(data->mycmd);
	}
	free_split(data->mycmdarg);
	free_split(data->paths);
	return (NULL);
}
