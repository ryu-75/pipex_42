/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:55:51 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/28 14:27:05 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// Return an error
void	ft_error(char *s)
{
	if (errno == 0)
		write(1, "Error\n", 6);
	else
		perror(s);
	exit(EXIT_FAILURE);
}

// Free each array create by ft_split
void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i])
			free(str[i++]);
	}
	free(str);
}

void	cmd_not_found(char **cmd)
{
	write (2, *cmd, ft_strlen(*cmd));
	ft_putstr_fd (": command not found\n", 2);
	free_split(cmd);
	exit(EXIT_FAILURE);
}


int	check_access(char *mycmd, char **mycmdarg, char **paths, int type)
{
	if (access(mycmd, type) == 0)
	{
		free_split(paths);
		free_split(mycmdarg);
		return (1);
	}
	return (0);
}
