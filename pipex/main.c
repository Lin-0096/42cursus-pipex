#include "pipex.h"

static void run_child(t_px *px, char *cmd_path, char **cmd_args, int index)
{
    int     redir_stdin;
    int     redir_strout;
    
    if(index == 1)
    {
        redir_stdin = px->filefd[0];
        redir_strout = px->pipefd[1];
    }
    if(index == 4)
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
    error_exit("execve");
}

static int  open_file(t_px *px, int index)
{
    int filefd;
    char *filename;

    filename = px->argv[index];
    if (index == 1)
    {
        filefd = open(filename, O_RDONLY);
        if (filefd == -1)
        {
            close_everything(px, 0, 0); //??
            error_exit(filename); //do i need to close sth?
        }
    }
    if (index == 4)
    {
        filefd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
        if (filefd == -1)
        {
            close_everything(px, 0, 0);
            error_exit(filename);
        }
    }
    return (filefd);
}
static void handle_child(t_px *px, int index)
{
    char **cmd_args;
    char *cmd_path;

    if (index == 1)
    {
        px->filefd[0] = open_file(px, index);
        cmd_args = split_cmd(px->argv[index + 1]);
    }
    if (index == 4)
    {
        px->filefd[1] = open_file(px, index);
        cmd_args = split_cmd(px->argv[index - 1]);
    }
    cmd_path = find_pass_cmd(px, cmd_args);
    run_child(px, cmd_path, cmd_args, index);
}

static int  child_process(t_px *px, int index)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        close_everything(px, 0, 0);
        error_exit("fork failed");
    }
    if (pid == 0)
    {
        handle_child(px, index);
    }
    return (pid);
}

int main(int argc, char **argv, char **envp)
{
    t_px    px;
    pid_t   pid[2];
    int     status[2];
    
    if(argc != 5)
    {
        ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", STDIN_FILENO);
        exit(EXIT_FAILURE);
    }
    px.argv = argv;
    px.envp = envp;
    px.filefd[0] = -1;
    px.filefd[1] = -1;
    if(pipe(px.pipefd) < 0) // ==0 success, -1 fail
        error_exit("pipe failed");
    pid[0] = child_process(&px, 1);
    pid[1] = child_process(&px, 4);
    close_everything(&px, 0, 0);
    waitpid(pid[0], &status[0], 0);//??
    waitpid(pid[1], &status[1], 0); 
    if (WIFEXITED(status[1]))
		return (WEXITSTATUS(status[1]));//modify
	return (EXIT_FAILURE);
}
