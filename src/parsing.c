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
char    *return_path(char **envp, char *cmd, char *av)
{
    int i;
    char    **paths;
    char    **mycmdarg;
    char    *mycmd;

    (void)av;
    i = -1; // Initialize the counter
    paths = get_path(envp); // We retrieve the path
    mycmdarg = ft_split(cmd, ' ');
    while (paths[++i])
    {
        paths[i] = ft_strjoin(paths[i], "/");
        mycmd = ft_strjoin(paths[i], *mycmdarg);
        if (access(mycmd, X_OK) == 0)
            return (mycmd);
        free(mycmd);
    }
    free(mycmdarg);
    return (NULL);
}