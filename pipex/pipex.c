/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:33:35 by linliu            #+#    #+#             */
/*   Updated: 2025/06/03 15:19:37 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int     pipefd[2];
    int     infile;
    int     outfile;
    pid_t   pid;
    
    if(argc != 5)
    {
        printf("Usage: ./pipex infile cmd1 cmd2 outfile\n");
        return(1);
    }
    infile = open(argv[1], O_RDONLY); //
    outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0664);//

    if(pipe(pipefd) == -1)
    {
        perror("pipe");
	    exit(1);
    }
    pid1 = child_process();
    pid2 = child_process();
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

//-----------------------------------------------
// creat pipe and fork
int pipefd[2];
if (pipe(pipefd) == -1)
{

}
int infile = open(argv[1], O_RDONLY);
int outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0664);
// 0 → just tells it's octal
// 6 → owner can read (4) + write (2)
// 4 → group can read
// 4 → others can read

pid_t pid1 = fork();
if (pid1 == 0)
{
    dup2(infile, STDIN_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    //close
    //execve
}

pid_t pid2 = fork();
if (pid2 == 0)
{
    dup2(pipefd[0], STDIN_FILENO);
    dup2(outfile, STDOUT_FILENO);
    //close
    execve(cmd_path, cmd_args, envp)
}

waitpid(pid1, NULL, 0);
waitpid(pid2, NULL, 0);

//---------------------------------------
//
char **parse_cmd(char *cmd)
{
    char **cmd_args = ft_split(cmd, ' ');
    if(!cmd_args)
        return (NULL);
    char *cmd_path = get_cmd_path(cmd_args[0], envp);
}