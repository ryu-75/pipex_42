/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:44:39 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/17 13:52:37 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* We truncate the unix command with path,
it's allow to applicate the command on it */

static char	**get_env(char **envp)
{
	int	i;
	char	**split_path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	split_path = ft_split(envp[i] + 5, ':');
	return (split_path);
}

char	*check_cmd(char *cmd, char **envp)
{
	if (!*envp)
	{
		if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
			return (cmd);
	}
	return (NULL);
}

char	*return_path(t_pipex *data, char *cmd, char **envp)
{	
	int	i;
	
	i = -1;

	check_cmd(cmd, envp);
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	data->paths = get_env(envp);
	data->mycmdarg = ft_split(cmd, ' ');
	while (data->paths[++i])
	{
		data->part_path = ft_strjoin(data->paths[i], "/");
		data->mycmd = ft_strjoin(data->part_path, *data->mycmdarg);
		free(data->part_path);
		if (access(data->mycmd, X_OK) == 0)
			return (data->mycmd);
		free(data->mycmd);
	}
	free_split(data->mycmdarg);
	free_split(data->paths);
	return (NULL);
}
