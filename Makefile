# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dberger <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 12:00:30 by dberger           #+#    #+#              #
#    Updated: 2019/10/15 16:22:13 by ncoursol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NO_COLOR = \033[0m
YELLOW = \033[33m
GREEN = \033[32m
BLUE = \033[36m
PINK = \033[35m

NAME = lem-in
NAME_DISP = display
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined -g
HFILE = ./include/lem-in.h
LIB_DIR = ./lib
OBJ_DIR = ./obj

LIBC = $(LIB_DIR)/libft
FT_PRINTF = $(LIB_DIR)/ft_printf
MINILIBX = $(LIB_DIR)/minilibx

NAME_PTF = libftprintf.a
NAME_LIBC = libft.a

SRC = src/main.c \
	  src/ft_storage.c \
	  src/ft_hashtab.c \
	  src/ft_bfs.c \
	  src/ft_links.c \
	  src/ft_karp.c

SRC_DISP = src/src_display/main.c \
		   src/src_display/menu.c

OBJ = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRC))


LIB = $(FT_PRINTF)/$(NAME_PTF) \
	  $(LIBC)/$(NAME_LIBC)

.PHONY: all clean fclean re

all: $(NAME)

$(LIB): FORCE
	$(MAKE) -C $(LIBC)
	$(MAKE) -C $(FT_PRINTF)

$(NAME): $(LIB) $(OBJ) Makefile $(HFILE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(CGFLAGS)
	gcc -o $(NAME_DISP) $(SRC_DISP) $(LIB) $(CGFLAGS)  -L lib/sdl -l SDL2-2.0.0 -l SDL2_image -l SDL2_gfx
	echo "$(YELLOW)	--- $(GREEN)lem-in$(YELLOW) Compiled ! ---	$(NO_COLOR)"

$(OBJ_DIR)/%.o:src/%.c $(HFILE)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(MAKE) $@ -C $(LIBC)
	$(MAKE) $@ -C $(FT_PRINTF)
	rm -rf $(OBJ_DIR)/$(OBJ)
	echo "$(BLUE)	--- Binary deleted ! ---	$(NO_COLOR)"

fclean: clean
	$(MAKE) $@ -C $(LIBC)
	$(MAKE) $@ -C $(FT_PRINTF)
	@rm -rf $(NAME)
	@rm -rf $(NAME_DISP)
	@echo "$(PINK)	--- Programm deleted ! ---	$(NO_COLOR)"

re: fclean all

.SILENT:

FORCE:
