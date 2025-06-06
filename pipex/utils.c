/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linliu <linliu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:01:04 by linliu            #+#    #+#             */
/*   Updated: 2025/06/06 11:01:07 by linliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    error_exit(const char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}

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
