NAME = minishell
CC = cc

FLAG = -Wall -Werror -Wextra -g3

SRC =	src/main.c\
		src/parsing/parsing.c\
		src/utils/utils.c\

OBJ_PATH = Bin/
OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))



PRINTF_DIR = printf
PRINTF_LIB = printf/libftprintf.a

LIBFT_DIR = libft
LIBFT_LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB) $(PRINTF_LIB)
	$(CC) $(FLAG) -o $(NAME) $(OBJ) -lreadline $(LIBFT_LIB) $(PRINTF_LIB)

$(OBJ_PATH)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(FLAG) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF_LIB):
	$(MAKE) -C $(PRINTF_DIR)

clean:
	rm -rf $(OBJ_PATH)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
