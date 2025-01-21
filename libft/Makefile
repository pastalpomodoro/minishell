# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 09:46:20 by rbaticle          #+#    #+#              #
#    Updated: 2025/01/21 16:44:18 by rbaticle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Werror -Wextra

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	   ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	   ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	   ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	   ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	   ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	   ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	   ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_strcmp.c ft_strndup.c
OBJS = $(SRCS:.c=.o)

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
		ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS_BONUS = $(BONUS:.c=.o)

GNL = get_next_line.c
GNL_OBJS = $(GNL:.c=.o)

PRINTF = ft_printf.c ft_printf_utils/ftf_putchar_fd.c \
		 ft_printf_utils/ftf_putnbr_fd.c \
		 ft_printf_utils/ftf_putstr_fd.c
PRINTF_OBJS = $(PRINTF:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(OBJS_BONUS) $(NAME)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

gnl: $(OBJS) $(GNL_OBJS)
	ar rcs $(NAME) $(OBJS) $(GNL_OBJS)

printf: $(OBJS) $(PRINTF_OBJS)
	ar rcs $(NAME) $(OBJS) $(PRINTF_OBJS)

gnl_bonus: $(OBJS) $(OBJS_BONUS) $(GNL_OBJS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS) $(GNL_OBJS)

printf_bonus: $(OBJS) $(OBJS_BONUS) $(PRINTF_OBJS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS) $(PRINTF_OBJS)

printf_gnl: $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	ar rcs $(NAME) $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)

printf_gnl_bonus: $(OBJS) $(OBJS_BONUS) $(GNL_OBJS) $(PRINTF_OBJS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS) $(GNL_OBJS) $(PRINTF_OBJS)

clean:
	rm -fr $(OBJS) $(OBJS_BONUS) $(GNL_OBJS) $(PRINTF_OBJS)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: clean fclean re
