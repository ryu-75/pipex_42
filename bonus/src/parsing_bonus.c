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

/* We retrieve the path in a simple array and then we split at 
':' symbol for retrieve correctly it */
char	**get_path(t_pipex *data)
{
	int		i;
	char	**split_path;

	i = 0;
	while (ft_strnstr(data->envp[i], "PATH", 4) != 0)
			i++;
	split_path = ft_split(data->envp[i] + 5, ':');
	return (split_path);
}

/* We truncate the unix command with path,
it's allow to applicate the command on it */
char	*return_path(t_pipex *data, char *cmd)
{
	int		i;

	i = -1;
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
	return (0);
}

/**
 ***** Fixed : Catch correctly the argument into the av struct in parse
 ***** each arg entered
 * 
 */