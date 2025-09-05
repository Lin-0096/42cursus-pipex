/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:59:45 by linliu            #+#    #+#             */
/*   Updated: 2025/06/09 13:16:07 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char    *find_path_in_envp(t_px *px)
{
    char    *path_value;
    char    **envp;

    envp = px->envp; // do not use px->envp directly, otherwise it will change it's value afterwords
    if(!envp)
        return (NULL);
    while(*envp) //get path
    {
        if (ft_strncmp(*envp, "PATH=", 5) == 0) //
        {
            path_value = *envp + 5;
            return (path_value);
        } 
        envp++;
    }
    return (NULL);
}

static char    *match_cmd_in_path(char **paths, char *cmd_arg)
{
    int     i;
    char    *joinslash;
    char    *com_path;

    i = 0;
    while(paths[i]) //join cmd to different dir to check if the cmd is there and can run
    {
        joinslash = ft_strjoin(paths[i], "/");
        if (!joinslash)
            return (NULL);
        com_path = ft_strjoin(joinslash, cmd_arg);
        free(joinslash); //!!free it before return, because after return it can't free anymore
        if(!com_path)
            return (NULL);
        if(access(com_path, X_OK) == 0) //0 means ok, if it can be executed then free everything
            return (com_path);
        free(com_path);
        i++;
    }
    return (NULL);
}

static char    *get_cmd_path(char *cmd_arg, t_px *px)
{
    char **paths;
    char *com_path;
    char *path_value;

    path_value = find_path_in_envp(px);
    if(!path_value)
        return (NULL);
    paths = ft_split(path_value, ':'); //split directory
    if(!paths)
        return (NULL);
    com_path = match_cmd_in_path(paths, cmd_arg);
    free_arr(paths);
    return (com_path);
}

char **split_cmd(char *whole_cmd)
{
    char **cmd_args;

    if(!whole_cmd)
        return (NULL);
    cmd_args = ft_split(whole_cmd, ' ');
    if(!cmd_args)
        return (NULL);
    return (cmd_args);
}

char *find_pass_cmd(t_px *px, char **cmd_args)
{
    char *path;

    path = get_cmd_path(cmd_args[0], px);
    if(!path)
    {
        ft_putstr_fd("Pipex: ", STDERR_FILENO);
        ft_putstr_fd(cmd_args[0], STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        close_everything(px, cmd_args, 0);
        exit(127);
    }
    return (path);
}