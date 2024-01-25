# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: long <long@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 10:46:34 by long              #+#    #+#              #
#    Updated: 2023/12/30 22:21:10 by long             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
AR = ar -rc
RM = rm -f
SRCS_DIR = srcs/
SRCS_FIL = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalpha.c ft_isalnum.c \
			ft_isdigit.c ft_isascii.c ft_isprint.c ft_memchr.c ft_memcmp.c \
			ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c \
			ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_tolower.c ft_toupper.c ft_itoa.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
			ft_print_num.c ft_print_str.c ft_printf_utils.c ft_printf.c \
			get_next_line_utils.c get_next_line.c
			
SRCS := $(addprefix $(SRCS_DIR), $(SRCS_FIL))
HEADER = ./includes/
CFLAGS = -Wall -Wextra -Werror
OPTION = -I $(HEADER)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(OPTION) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
