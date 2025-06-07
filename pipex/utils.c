/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lin <lin@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:01:04 by linliu            #+#    #+#             */
/*   Updated: 2025/06/07 13:19:30 by lin              ###   ########.fr       */
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

void    error_exit(const char *str, int error_code)
{
    perror(str);
    exit(error_code); //modify
}

// Standard Unix/Linux Exit Codes

// Exit     Code	             Meaning	Example Use Cases
// 0	   Success	             All commands executed successfully
// 1	   General               error	Catch-all for miscellaneous errors
// 126	   Command               not executable (permission denied)	Command exists but lacks execute permissions
// 127	   Command               not found	Command doesn't exist or isn't in PATH
// 128+N   Process terminated by signal N	  e.g., kill -9 returns 137 (128+9)
