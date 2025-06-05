CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME := pipex
SRCS := main.c get_cmd_path.c utils.c
OBJ := $(SRCS:%.c=%.o)

RM := rm -f

all: $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJ)

		 
