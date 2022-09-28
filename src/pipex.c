/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:55:43 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/28 12:43:17 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	fd_dup[2];

	if (ac < 5)
	{
		ft_putstr_fd("Expected : file1 [cmd1] [cmd2] file2\n", 2);
		exit(0);
	}
	else
	{
		if (pipe(fd_dup) < 0)
			ft_error("pipe");
		else
			pipex(av, fd_dup, envp);
	}
	return (0);
}
