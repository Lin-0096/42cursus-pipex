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
