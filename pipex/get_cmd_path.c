#include "pipex.h"

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

char    *get_cmd_path(char *cmd_arg, t_px *px)
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

static char    *find_path_in_envp(t_px *px)
{
    char    *path_value;
    char    **envp;

    envp = px->envp; // do not use px->evnp directly, otherwise it will change it's value afterwords
    if(!envp)
        return (NULL);
    while(*envp) //get path
    {
        if (ft_strncmp(*envp, "PATH=", 5) == 0)
        {
            path_value = *envp + 5;
            return (path_value);
        } 
        envp++;
    }
    return (NULL);
}

static  char    *match_cmd_in_path(char **paths, char *cmd_arg)
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
        if(access(com_path, X_OK) == 0) //if it can be executed then free everything
            return (com_path);
        free(com_path);
        i++;
    }
    return (NULL);
}

