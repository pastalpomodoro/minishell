NAME = minishell
CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

SRCS_DIR = ./srcs/
SRCS_NAMES = main.c \
			 utils/utils.c \
			 utils/utils2.c \
			 utils/ft_split2.c \
			 utils/variadic_strjoin.c \
			 utils/get_path.c \
			 tokens/tokenize.c \
			 tokens/split_token.c \
			 tokens/check_spaces.c \
			 tokens/insert_spaces.c \
			 tokens/delete_useless.c \
			 tokens/add_token.c \
			 tokens/tkn_lst.c \
			 tokens/check_wildcards.c \
			 tokens/get_wildcard.c \
			 env/env_creator.c \
			 env/replace_var.c \
			 env/replace_var_utils.c \
			 env/search_env.c \
			 lst_creator/lst_creator.c \
			 lst_creator/lst_redir.c \
			 lst_creator/lst_cmd.c \
			 lst_creator/lst_creator_utils.c \
			 execution/execution.c \
			 execution/and_or_execution.c \
			 cmds/echo.c \
			 cmds/env.c \
			 cmds/export.c \
			 cmds/pwd.c \
			 cmds/cd.c \
			 cmds/exit.c \
			 sig/signals.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_NAMES))

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

LIBFT_DIR = libft
LIBFT_LIB = libft/libft.a

INCLUDES = ./includes/
HEADER_FILES = functions.h macros.h minishell.h structs.h
HEADERS = $(addprefix $(INCLUDES), $(HEADER_FILES))

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -L $(LIBFT_DIR) -lft -I $(INCLUDES) -o $(NAME)

$(OBJ_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@) # Crée les répertoires nécessaires
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(LIBFT_LIB):
	@make printf -C $(LIBFT_DIR)

fsan: $(LIBFT_LIB) $(HEADERS)
	$(CC) $(CFLAGS) -g3 -fsanitize=address $(SRCS) -lreadline -L $(LIBFT_DIR) -lft -I $(INCLUDES) -o $(NAME)

debug: $(LIBFT_LIB) $(HEADERS)
	$(CC) $(CFLAGS) -g3 $(SRCS) -lreadline -L $(LIBFT_DIR) -lft -I $(INCLUDES) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

