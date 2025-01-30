NAME = minishell
CC = cc

CFLAGS = -Wall -Werror -Wextra

SRCS_DIR = ./srcs/
SRCS_NAMES = main.c \
			 parsing/parsing.c \
			 utils/utils.c \
			 utils/ft_split2.c \
			 utils/variadic_strjoin.c \
			 tokens/tokenize.c \
			 tokens/split_token.c \
			 tokens/check_spaces.c \
			 tokens/insert_spaces.c \
			 tokens/add_token.c \
			 tokens/tkn_lst.c \
			 env/env_creator.c \
			 env/replace_var.c \
			 env/search_env.c
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

fsan: $(LIBFT_LIB) $(HEADERS)
	$(CC) $(CFLAGS) -g3 -fsanitize=address $(SRCS) -lreadline -L $(LIBFT_DIR) -lft -I $(INCLUDES) -o $(NAME)

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
