# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 20:43:24 by htharrau          #+#    #+#              #
#    Updated: 2025/02/16 14:47:39 by htharrau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	=   ft_atoi.c		ft_itoa.c		ft_putnbr_fd.c	ft_strlcpy.c	\
			ft_substr.c  	ft_bzero.c		ft_memchr.c 	ft_putstr_fd.c	\
			ft_strlen.c		ft_tolower.c	ft_calloc.c		ft_memcmp.c		\
			ft_split.c		ft_strmapi.c	ft_toupper.c	ft_isalnum.c	\
			ft_memcpy.c		ft_strchr.c		ft_strncmp.c	ft_isalpha.c	\
			ft_memmove.c	ft_strdup.c		ft_strnstr.c	ft_isascii.c	\
			ft_memset.c		ft_striteri.c	ft_strrchr.c	ft_isdigit.c	\
			ft_putchar_fd.c	ft_strjoin.c	ft_strtrim.c	ft_isprint.c	\
			ft_putendl_fd.c	ft_strlcat.c	ft_strcmp.c						\
			ft_lstnew.c		ft_lstsize.c	ft_lstlast.c	ft_lstdelone.c	\
			ft_lstclear.c	ft_lstiter.c	ft_lstmap.c 					\
			ft_lstadd_back.c	ft_lstadd_front.c	get_next_line_bonus.c	\
			ft_printf.c 	ft_spec.c 		ft_put.c 		ft_length.c

OBJS	= $(SRCS:.c=.o)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g

.SILENT:

$(NAME): $(OBJS)
	ar rc	$(NAME)	$(OBJS)
	ranlib $(NAME)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

