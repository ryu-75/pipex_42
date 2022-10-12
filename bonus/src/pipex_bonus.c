/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:25:59 by sasha             #+#    #+#             */
/*   Updated: 2022/10/12 15:13:35 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;
	int	i;

	i = 2;
	init_value(&data, av, envp, ac);
	if (data.ac >= 5)
	{
		data.fd_in = open(av[1], O_RDONLY);
		data.fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dup2(data.fd_in, STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
		close(data.fd_in);
		dup2(data.fd_out, STDOUT_FILENO);
		close(data.fd_out);
		while (i < data.ac - 2)
			ft_process(&data, data.av[i++]);
		exec_cmd(&data, data.av[i]);
	}
	else
	{
		ft_putstr_fd("Expected : file1 [cmd1] [cmd2] file2\n", 2);
		exit(0);
	}
	return (1);
}