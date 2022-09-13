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
    int i;

    i = 0;
    size = ft_strlen(*str);
    while (i < size)
    {
        if (*str)
            free(str[i]);
        i++;
    }
}

//  Returns - cmd : command not found - if the cmd[2] or cmd[3] is not found
char    *cmd_not_found(char **cmd)
{
    write (2, &cmd[0], ft_strlen(cmd[0]));
    write(2, ": command not found\n", 20);
    free_split(cmd);
    return (NULL);
}