/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:55:51 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/07 15:55:51 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// Return an error
int ft_error(char *s)
{
    if (errno == 0)
        return (EXIT_FAILURE);
    else
        perror(s);
    return (EXIT_FAILURE);
}

// Free each array create by ft_split
void    free_split(char **str)
{
    int size;

    size = ft_strlen(*str);
    while (size)
    {
        if (*str)
            free(str[--size]);
    }
    free(str);
}

//  Returns - cmd : command not found - if the cmd[2] or cmd[3] is not found
void    cmd_not_found(char *cmd)
{
    write (2, cmd, ft_strlen(cmd));
    write(2, ": command not found\n", 20);
    free(cmd);
    exit(0);
}