/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:33:35 by linliu            #+#    #+#             */
/*   Updated: 2025/06/06 17:43:09 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

//create pipe before the fork, check them every time call them
//waitpid to avoid child-process becoming zombie-process
//exit(EXIT_FAILURE) if there's no reasonable way to continue,it is more readable and portable than exit(1)

static void run_child1(t_px *px, char **cmd_args, char *cmd_path)
{
    dup2(px->filefd[0], STDIN_FILENO);
    dup2(px->pipefd[1], STDOUT_FILENO);
    close(px->filefd[0]);
    close(px->filefd[1]);//Output file (not used)
    close(px->pipefd[0]); //Pipe read end (not used)
    close(px->pipefd[1]);
    
    execve(cmd_path, cmd_args, px->envp);
    free_arr(cmd_args); 
    free(cmd_path);
    error_exit("execve");
}

static int  child1_process(t_px *px)
{
    pid_t pid;
    char **cmd_args;
    char *cmd_path;

    cmd_args = split_cmd(px->argv[2]);
    if (!cmd_args)
        error_exit("split_cmd failed"); //don't need to free， cause i free everything in ft_split if fails
    cmd_path = get_cmd_path(cmd_args[0], px);
    if(!cmd_path)
    {
        free_arr(cmd_args);
        error_exit("command not found");
    }
    pid = fork();
    if(pid < 0) //pid=0 child process, pid>0 parent process, pid<0 failed
    {
        free_arr(cmd_args);
        free(cmd_path);
        error_exit("fork");
    }
    if (pid == 0)
        run_child1(px, cmd_args, cmd_path);
    return (pid);
}

static void run_child2(t_px *px, char **cmd_args, char *cmd_path)
{
    dup2(px->pipefd[0], STDIN_FILENO);
    dup2(px->filefd[1], STDOUT_FILENO);
    close(px->filefd[0]);
    close(px->filefd[1]);
    close(px->pipefd[0]);
    close(px->pipefd[1]);
    printf("Child 2: Executing command\n");
    execve(cmd_path, cmd_args, px->envp);
    free_arr(cmd_args);
    free(cmd_path);
    error_exit("execve");
}

static int  child2_process(t_px *px)
{
    pid_t pid;
    char **cmd_args;
    char *cmd_path;

    cmd_args = split_cmd(px->argv[3]);
    if(!cmd_args)
        error_exit("split_cmd failed");
    cmd_path = get_cmd_path(cmd_args[0], px);
    if (!cmd_path)
    {
        free_arr(cmd_args);
        error_exit("command not found");
    }
    pid = fork();
    if(pid < 0)
     {
        free_arr(cmd_args);
        free(cmd_path);
        error_exit("fork");
     }
    if (pid == 0)
       run_child2(px, cmd_args, cmd_path);
    return (pid);
}

int main(int argc, char **argv, char **envp)
{
    t_px    px;
    pid_t   pid[2];
    int     status[2];
    
    if(argc != 5)
        error_exit("Usage: ./pipex infile cmd1 cmd2 outfile");
        
    px.argv = argv;
    px.envp = envp;
    
    px.filefd[0] = open(argv[1], O_RDONLY);
    if (px.filefd[0] < 0 )
        error_exit("open file");
    px.filefd[1] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (px.filefd[1] < 0 )
    {
        close(px.filefd[0]);
        error_exit("open file");
    }
    if(pipe(px.pipefd) < 0)
        error_exit("pipe");
    pid[0] = child1_process(&px);
    pid[1] = child2_process(&px);
    close(px.pipefd[0]); //close the ends in the parent, otherwise lead to file descriptor leaks and unexpected behavior
    close(px.pipefd[1]);
    waitpid(pid[0], &status[0], 0);
    waitpid(pid[1], &status[1], 0); 
    if (WIFEXITED(status[0]) && WEXITSTATUS(status[0]) != 0)
        fprintf(stderr, "Command 1 failed: %s\n", argv[2]);
    if (WIFEXITED(status[1]) && WEXITSTATUS(status[1]) != 0)
        fprintf(stderr, "Command 2 failed: %s\n", argv[3]);//??
        
    if (WIFEXITED(status[1]))
	    return (WEXITSTATUS(status[1]));
    else
	    return (0);
}






