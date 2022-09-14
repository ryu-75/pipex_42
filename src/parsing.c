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
    char    *path;
    char    **split_path;
    int i;

    i = 0;
    path = malloc(sizeof(char *) + ft_strlen(envp[i]) + 1);
    if (!path)
        return (NULL);
    while(!ft_strnstr(envp[i], "PATH", 4))
        i++;
    path = envp[i];
    path = ft_substr(envp[i], 5, ft_strlen(path));
    split_path = ft_split(path, ':');
    free(path);
    return (split_path);
}

// We truncate the unix command with path, it's allow to applicate the command on it
char    *return_path(char **envp, char *cmd, char **av)
{
    int i;
    char    **path;
    char    **mycmdarg;

    i = -1; // Initialize the counter
    path = get_path(envp); // We retrieve the path
    mycmdarg = ft_split(cmd, ' ');
    while (path[++i])
    {
        cmd = ft_strjoin(path[i], "/");
        cmd = ft_strjoin(cmd, *av);
        if (cmd && path)
            execve(cmd, mycmdarg, envp);
        else
            perror("Error");
        free(cmd);
    }
    return (NULL);
}