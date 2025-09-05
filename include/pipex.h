/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:00:26 by linliu            #+#    #+#             */
/*   Updated: 2025/09/05 14:59:14 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> //execve, dup2
# include <fcntl.h> //open
# include <stdlib.h> //exit（）malloc free
# include <sys/wait.h> // waitpid
# include <stdio.h> //perror
# include "libft.h"

typedef struct  s_px
{
	char	**argv;
	char	**envp;
	int		filefd[2];   // filefd[0] infile,filefd[1] outfile
	int		pipefd[2];   // pipefd[0] read,pipefd[1] write
}   t_px;

char    **split_cmd(char *whole_cmd);
char 	*find_pass_cmd(t_px *px, char **cmd_args);

void    error_exit(const char *str);
void    free_arr(char **str);
void    close_everything(t_px *px, char **cmd_args, char *cmd_path);

#endif
