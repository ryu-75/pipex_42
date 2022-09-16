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
void    ft_error(char *s, char **cmd, char *path)
{
    perror(s);
    all_free(path, cmd);
    exit(0);
}

// Free each array create by ft_split
void    free_split(char **str)
{
    int i;

    i = 0;
    while (str[i] != 0)
    {
        if (*str)
            free(str[i++]);
    }
    free(str);
}

//  Returns - cmd : command not found - if the cmd[2] or cmd[3] is not found
void    cmd_not_found(char **cmd)
{
    write (2, *cmd, ft_strlen(*cmd));
    write(2, ": command not found\n", 20);
}

void    all_free(char *path, char **cmd)
{
    free_split(cmd);
    free(path);
}