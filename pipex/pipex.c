/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lin <lin@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:33:35 by linliu            #+#    #+#             */
/*   Updated: 2025/06/04 18:27:53 by lin              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //execve, dup2
#include <fcntl.h> //open things
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
    int     infile;
    int     outfile;
    pid_t   pid[2];
    
    if(argc != 5)
        return(1);
    infile = open(argv[1], O_RDONLY);
    outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if(infile == -1 || outfile == -1)
    {
        
    }
    
    pid[0] = child1_process(argv, infile, 1, envp);
    pid[1] = child2_process(argv, outfile, 0, envp);
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0); 
    return(0);
}

//-------------------------------------------------------
//get_cmd_path and check if it can run
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

char **split_cmd(char *cmd, char **envp)
{
    if(!cmd)
    {
        
    }
    char **cmd_args = ft_split(cmd, ' ');
    if(!cmd_args)
        return (NULL);
}

int    child1_process(char **argv, int file_fd, int pipe_nub, char **envp)
{
    int pipefd[2];
    pid_t pid;
    char **cmd_args = split_cmd(argv[2], envp);
    char *cmd_path = get_cmd_path(cmd_args[0], envp);

    if(pipe(pipefd) < 0)
    {
        
    }
    pid = fok();
    if(pid < 0)
    {
       
        
    }
    if (pid == 0)
    {
        dup2(file_fd, STDIN_FILENO);
        dup2(pipefd[pipe_nub], STDOUT_FILENO);
        close(file_fd);
        close(pipefd[pipe_nub]);
        execve(cmd_path, cmd_args, envp);
    }
    return (pid);
}
