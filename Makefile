NAME = fdf
CC = gcc
AR = ar -rc
RM = rm -f
SRCS = test.c
LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a
CFLAGS = -Wall -Wextra -Werror
OPTION = -I ./
# MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
MLXFLAGS = -Imlx -L mlx/minilibx_macos/ -lmlx -framework OpenGL -framework AppKit

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

bonus: all

clean:
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
