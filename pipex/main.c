/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lin <lin@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:33:35 by linliu            #+#    #+#             */
/*   Updated: 2025/06/07 13:28:18 by lin              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

//create pipe before the fork, check them every time call them
//waitpid to avoid child-process becoming zombie-process
//exit(EXIT_FAILURE) if there's no reasonable way to continue,it is more readable and portable than exit(1)

static void run_child(t_px *px, char **cmd_args, char *cmd_path, int cmd_index)
{
    int redir_stdin;
    int redir_strout;
    
    if(cmd_index == 2)
    {
        redir_stdin = px->filefd[0];
        redir_strout = px->pipefd[1];
    }
    if(cmd_index == 3)
    {
        redir_stdin = px->pipefd[0];
        redir_strout = px->filefd[1];
    }
    dup2(redir_stdin, STDIN_FILENO);
    dup2(redir_strout, STDOUT_FILENO);
    close_everything(px, 0, 0);
    execve(cmd_path, cmd_args, px->envp);
    free_arr(cmd_args);
    free(cmd_path);
    error_exit("execve", 126);
}

static int  child_process(t_px *px, int cmd_index)
{
    pid_t pid;
    char **cmd_args;
    char *cmd_path;

    cmd_args = split_cmd(px->argv[cmd_index]);
    if(!cmd_args)
        error_exit("split_cmd failed", 1);//don't need to free， cause i free everything in ft_split if fails
    cmd_path = get_cmd_path(cmd_args[0], px);
    if (!cmd_path)
    {
        free_arr(cmd_args);
        error_exit("command not found", 127);
    }
    pid = fork();
    if(pid < 0) //pid=0 child process, pid>0 parent process, pid<0 failed
     {
        close_everything(px, cmd_args, cmd_path);
        error_exit("fork failed", 1);
     }
     if (pid == 0)
        run_child(px, cmd_args, cmd_path, cmd_index);
    return (pid);
}

int main(int argc, char **argv, char **envp)
{
    t_px    px;
    pid_t   pid[2];
    int     status;
    
    if(argc != 5)
        error_exit("Usage: ./pipex infile cmd1 cmd2 outfile", 1);
    px.argv = argv;
    px.envp = envp;
    px.filefd[0] = open(argv[1], O_RDONLY);
    if (px.filefd[0] < 0 )
        error_exit("open file", 1);
    px.filefd[1] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (px.filefd[1] < 0 )
    {
        close(px.filefd[0]);
        error_exit("open file", 1);
    }
    if(pipe(px.pipefd) < 0)
        error_exit("pipe failed", 1);
    pid[0] = child_process(&px, 2);
    pid[1] = child_process(&px, 3);
    close(px.pipefd[0]); //close the ends in the parent, otherwise lead to file descriptor leaks and unexpected behavior
    close(px.pipefd[1]);
    waitpid(pid[0], &status, 0);
    waitpid(pid[1], &status, 0); 
    if (WIFEXITED(status))
		return (WEXITSTATUS(status));//modify
	return (0);
}






