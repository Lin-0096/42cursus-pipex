#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h> //execve, dup2
#include <fcntl.h> //open things
#include <stdlib.h> //exit（）
#include <sys/wait.h> // waitpid
#include <stdio.h> //perror

//get_cmd_path and check if it can run
char    *get_cmd_path(char *cmd, char **envp);
char    **split_cmd(char *cmd, char **envp);

void    error_exit(const char *str);
void    free_arr(char **str);


#endif