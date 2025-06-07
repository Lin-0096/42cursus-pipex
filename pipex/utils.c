/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lin <lin@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:01:04 by linliu            #+#    #+#             */
/*   Updated: 2025/06/07 18:28:30 by lin              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    free_arr(char **str)
{
    int i;

    if(!str)
        return ;
    i = 0;
    while(str[i])
        free(str[i++]);
    free(str);
}

void    close_everything(t_px *px, char **cmd_args, char *cmd_path)
{
    if (cmd_args)
        free_arr(cmd_args);
    if (cmd_path)
        free(cmd_path);
    if (px->filefd[0] != -1)
        close(px->filefd[0]);
    if (px->filefd[1] != -1)
        close(px->filefd[1]);
    if (px->pipefd[0] != -1)
        close(px->pipefd[0]);
    if (px->pipefd[1] != -1)
        close(px->pipefd[1]);
}

void    error_exit(const char *str)
{
    perror(str);
    exit(EXIT_FAILURE); //modify
}

// Standard Unix/Linux Exit Codes
// Exit     Code	             Meaning	                       Example Use Cases
// 0	   Success	             All commands executed successfully
// 1	   General               error	                Catch-all for miscellaneous errors
// 126	   Command               not executable (permission denied)	  Command exists but lacks execute permissions
// 127	   Command               not found	             Command doesn't exist or isn't in PATH
// 128+N   Process terminated by signal N	  e.g., kill -9 returns 137 (128+9)


//errno aotu-set, indicate specific error ,system error number, system can tell the spesifc error message through the errno
//errno is automatically set by the system on failure
//error, use perror to print error message
//mistake can be devided into 2 types, system error and logical error, so when we check the error and exit,
//we can use if to differ them.
//logical error no errno, error is 0, use ft_putstr_fd(msg)to print
//Use 1 for general errors (system or logical).
//Reserve 127 for "command not found" (matching shell conventions).
//Use 126 for permission-related failures
//strerror() converts error codes to human-readable strings

// void    error_exit(char *msg, int exit_code)
// {
//     if(errno)
//     {
        
//     }
// }