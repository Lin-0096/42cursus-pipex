CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME := pipex
SRCS := src/main.c src/path.c src/utils.c
OBJ := $(SRCS:%.c=%.o)

LIBFT_PATH := libft
LIBFT := $(LIBFT_PATH)/libft.a
INCLUDE := -I include -I libft

RM := rm -f

all: $(LIBFT) $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
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
