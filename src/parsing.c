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

char	**get_path(t_pipex *data)
{
	int	i;
	char	**split_path;
	i = 0;	
	while (!ft_strnstr(data->envp[i], "PATH=", 5))
		i++;
	split_path = ft_split(data->envp[i] + 5, ':');
	return (split_path);
}

char	*return_path(t_pipex *data, char *cmd)
{
	int		i;

	i = -1;
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	data->paths = get_path(data);
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

// char	*return_path(t_pipex *data, char *cmd)
// {
// 	data->mycmdarg = ft_split(cmd, ' ');
// 	if (ft_strnstr(data->mycmdarg[0], "/", ft_strlen(data->mycmdarg[0])))
// 	{
// 		// free_split(data->mycmdarg);
// 		return (cmd);
// 	}
// 	else if (!ft_strnstr(data->mycmdarg[0], "/", ft_strlen(data->mycmdarg[0])))
// 	{
// 		printf("1 : %s\n", cmd);
// 		get_path(data, cmd);
// 	}
// 	return (NULL);
// }