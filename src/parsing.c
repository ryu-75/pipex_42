/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:44:39 by nlorion           #+#    #+#             */
/*   Updated: 2022/09/06 17:44:39 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// We retrieve the path in a simple array and then we split at ':' symbol for retrieve correctly it
char    **get_path(char **envp)
{
    char    **split_path;
    int i;

    i = 0;
    while(!ft_strnstr(envp[i], "PATH", 4))
        i++;
    split_path = ft_split(envp[i] + 5, ':');
    return (split_path);
}

// We truncate the unix command with path, it's allow to applicate the command on it
char    *return_path(char **envp, char *cmd)
{
    int i;
    char    **paths;
    char    **mycmdarg;
    char    *mycmd;
    char    *part_path;

    i = -1;
    paths = get_path(envp);
    mycmdarg = ft_split(cmd, ' ');
    while (paths[++i])
    {
        part_path = ft_strjoin(paths[i], "/");
        mycmd = ft_strjoin(part_path, *mycmdarg);
        free(part_path);
        if (access(mycmd, X_OK) == 0)
        {
            free_split(paths);
            free_split(mycmdarg);
            return (mycmd);
        }
        free(mycmd);
    }
    free_split(paths);
    free_split(mycmdarg);
    return (NULL);
}