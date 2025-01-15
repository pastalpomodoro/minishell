NAME = minishell
CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

SRCS_DIR = ./srcs/
SRCS_NAMES = main.c \
			 parsing/parsing.c \
			 parsing/parsing_redir.c \
			 parsing/parsing_cmd.c \
			 utils/utils.c\
			 utils/ft_split2.c\
			 utils/utils_node.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_NAMES))
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_LIB = libft/libft.a

INCLUDES = ./includes/
HEADER_FILES = functions.h macros.h minishell.h structs.h
HEADERS = $(addprefix $(INCLUDES), $(HEADER_FILES))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -L $(LIBFT_DIR) -lft -I $(INCLUDES) -o $(NAME)

$(LIBFT_LIB):
	@make printf -C $(LIBFT_DIR)

fsanitize: $(LIBFT_LIB) $(HEADERS)
	$(CC) $(CFLAGS) -g3 -fsanitize=addresss $(SRCS) -lreadline -L $(LIBFT_DIR) -lft -I $(INCLUDES) -o $(NAME)

debug:$(LIBFT_LIB) $(HEADERS)
	$(CC) $(CFLAGS) -g3 $(SRCS) -lreadline -L $(LIBFT_DIR) -lft -I $(INCLUDES) -o $(NAME)

clean:
	rm -rf $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
