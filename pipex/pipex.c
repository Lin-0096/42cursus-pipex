/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lin <lin@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:33:35 by linliu            #+#    #+#             */
/*   Updated: 2025/06/02 22:54:38 by lin              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(int argc, char **argv)
{
    if(argc != 5)
    {
        printf("Usage: ./pipex infile cmd1 cmd2 outfile\n");
        return(1);
    }

    printf("infiel: %s\n", argv[1]);
    printf("cmd1: %s\n", argv[2]);
    printf("cmd2: %s\n", argv[3]);
    printf("outfiel: %s\n", argv[4]);

    return(0);
}

char *get_cmd_path(char *cmd, char **envp)
{
    char **paths;
    char *joinslash;
    int i;
    int j;
    char *com_path;
    char *path_value;

    while(*envp) //get path
    {
        if (ft_strncmp(*envp, "PATH=", 5) == 0)
            path_value = *envp + 5;
        *envp++;
    }
    if (!*envp)
        return (NULL);
    paths = ft_split(path_value, ':'); //split directory
    if(!paths)
        return (NULL);
    i = 0;
    while(paths[i]) //join cmd to different dir to check if the cmd is there and can run
    {
        joinslash = ft_strjoin(paths[i], "/"); //?do i have to check here
        com_path = ft_strjoin(joinslash, cmd);
        free(joinslash); //!!
        if(access(com_path, X_OK) == 0) //if it can be executed then free everything 
        {
            j = 0;
            while(paths[j])
                free(paths[j++]);
            free(paths); //!!
            return (com_path);
        }
        free(com_path);
        i++;
    }
    i = 0;
    while(paths[i]) //clean up everything then
        free(paths[i++]);
    free(paths);
    return (NULL);
}
// creat pipe and fork
int pipefd[2];
if (pipe(pipefd) == -1)
{

}
pid_t pid = fork();
if (pid == -1)
{

}
dup2(infile, STDIN_FILENO);
close(infile);

dup2(pipefd[1], STDOUT_FILENO);
close(pipefd[1]);
