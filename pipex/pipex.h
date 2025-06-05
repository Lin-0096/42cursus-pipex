#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> //execve, dup2
# include <fcntl.h> //open
# include <stdlib.h> //exit（）malloc free
# include <sys/wait.h> // waitpid
# include <stdio.h> //perror

typedef struct  s_px
{
	char	**argv;
	char	**envp;
	int		filefd[2];   // filefd[0] infile,filefd[1] outfile
	int		pipefd[2];   // pipefd[0] read,pipefd[1] write
}   t_px;

//get_cmd_path and check if it can run
char    *get_cmd_path(char *cmd_arg, t_px *px);
char    **split_cmd(char *whole_cmd);

void    error_exit(const char *str);
void    free_arr(char **str);

#endif