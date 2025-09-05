CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME := pipex
SRCS := main.c path.c utils.c
OBJ := $(SRCS:%.c=%.o)

LIBFT_PATH := ./libft/
LIBFT  := $(LIBFT_PATH)libft.a


RM := rm -f

all: $(LIBFT) $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJ) 
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT): 
		make -C	$(LIBFT_PATH)
clean:
	@$(RM) $(OBJ) 
	@ make clean -C $(LIBFT_PATH)

fclean: clean
	@ $(RM) $(NAME)
	@ make fclean -C $(LIBFT_PATH)

re: fclean all
	

.PHONY: all clean fclean re