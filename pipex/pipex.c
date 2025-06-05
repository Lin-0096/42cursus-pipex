/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lin <lin@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:33:35 by linliu            #+#    #+#             */
/*   Updated: 2025/06/05 13:39:28 by lin              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//create pipe before the fork, check them every time call them
//waitpid to avoid child-process becoming zombie-process
//exit(EXIT_FAILURE) if there's no reasonable way to continue,it is more readable and portable than exit(1)

int main(int argc, char **argv, char **envp)
{
    int pipefd[2];
    pid_t   pid[2];
    
    if(argc != 5)
        return(1);
    if(pipe(pipefd) < 0)
        error_exit("pipe");
    
    pid[0] = child1_process(argv, pipefd, envp);
    pid[1] = child2_process(argv, pipefd, envp);
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0); 
    return(0);
}

int    child1_process(char **argv, int *pipefd, char **envp)
{
    pid_t pid;
    int infile;
    char **cmd_args;
    char *cmd_path;

    cmd_args =split_cmd(argv[2], envp);
    if (!cmd_args)
        error_exit("split_cmd failed");
    cmd_path = get_cmd_path(cmd_args[0],envp);
    if(!cmd_path)
    {
        free_arr(cmd_args);
        error_exit("command not found");
    }
    infile = open(argv[1], O_RDONLY);
    if (infile < 0 )
        error_exit("open file");
    pid = fork();
    if(pid < 0)
        error_exit("fork");
    if (pid == 0)
    {
        dup2(infile, STDIN_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        close(infile);
        close(pipefd[0]);
        close(pipefd[1]);
        execve(cmd_path, cmd_args, envp);
        error_exit("exeve");
    }
    return (pid);
}

int    child2_process(char **argv, int *pipefd, char **envp)
{
    pid_t pid;
    int outfile;
    char **cmd_args = split_cmd(argv[3], envp);
    char *cmd_path = get_cmd_path(cmd_args[0], envp);

    outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (outfile < 0 )
        error_exit("open file");
    pid = fork();
    if(pid < 0)
        error_exit("fork");
    if (pid == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);
        dup2(outfile, STDOUT_FILENO);
        close(outfile);
        close(pipefd[0]);
        close(pipefd[1]);
        execve(cmd_path, cmd_args, envp);
        error_exit("exeve");
    }
    return (pid);
}





