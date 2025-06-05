#include "pipex.h"

char *get_cmd_path(char *cmd, char **envp)
{
    char **paths;
    char *com_path;
    char *path_value;

    path_value = find_path_in_envp(envp);
    if(!path_value)
        return (NULL);
    paths = ft_split(path_value, ':'); //split directory
    if(!paths)
        return (NULL);
    com_path = match_cmd_in_path(paths, cmd);
    free_arr(paths);
    return (com_path);
}

static char    *find_path_in_envp(char **envp)
{
    char    *path_value;

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

static  char    *match_cmd_in_path(char **paths, char *cmd)
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
        com_path = ft_strjoin(joinslash, cmd);
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

char **split_cmd(char *cmd, char **envp)
{
    char **cmd_args;

    if(!cmd || !envp)
        return (NULL);
    cmd_args = ft_split(cmd, ' ');
    if(!cmd_args)
        return (NULL);
    return (cmd_args);
}
