/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:55:43 by nlorion           #+#    #+#             */
/*   Updated: 2022/10/10 15:23:23 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;
	int	status;
	
	init_value(&data, av, envp, ac);
	if (ac < 5)
	{
		ft_putstr_fd("Expected : file1 [cmd1] [cmd2] file2\n", 2);
		exit(0);
	}
	else
	{
		if (pipe(data.fd_dups) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		else
		{
			init_fd(&data);
			child_process(&data);
			waitpid(-1, &status, 0);
		}
	}
	return (0);
}
