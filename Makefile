# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfiestas <lfiestas@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 07:17:39 by lfiestas          #+#    #+#              #
#    Updated: 2024/12/03 18:28:00 by lfiestas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Wno-unused-command-line-argument \
	-lm -ldl -lglfw -pthread

NAME = fractol
SRCS = main.c complex.c drawing.c fractals.c hooks.c utils.c
OBJS = $(patsubst %.c,%.o,$(SRCS))
MLX = MLX42/build/libmlx42.a

.PHONY: all mlx bonus debug clean fclean re
.PRECIOUS: $(TESTS_NAME) release_tests

all: CFLAGS += -O3 -ffast-math
all: $(NAME)

debug: CFLAGS += -ggdb3 -gdwarf
debug: CFLAGS += -fsanitize=address -fsanitize=undefined -fsanitize=leak
debug: $(NAME)

libft/libft.a:
	make -C libft -j4

mlx: $(MLX)

$(MLX):
	git clone https://github.com/codam-coding-college/MLX42.git
	cd MLX42 && cmake -B build
	cd MLX42 && cmake --build build -j4

$(NAME): $(OBJS) libft/libft.a $(MLX)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c fractol.h
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	make clean -C libft
	rm -f *.o

fclean: clean
	make fclean -C libft
	rm -rf MLX42
	rm -f $(NAME)

re: fclean all
