# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 19:03:50 by ncoursol          #+#    #+#              #
#    Updated: 2019/08/22 10:23:52 by ncoursol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NO_COLOR = \033[0m
COMP_COLOR = \033[33m
BIN_COLOR = \033[32m
BIN2_COLOR = \033[36m
PROG_COLOR = \033[35m

NAME = libftprintf.a
CC = gcc
FLAGS = -Wall -Wextra -Werror

LIB_DIR = ../libft

SOURCES = ft_format_csp.c\
ft_format_di.c\
ft_nan_inf.c\
ft_print_float.c\
ft_format_f.c\
ft_format_u.c\
ft_format_xx.c\
ft_check_add.c\
ft_check_char.c\
ft_convert.c\
ft_printf.c\
ft_ltoa.c\
ft_ftoa.c\
ft_utoa.c\
ft_dtoh.c\
ft_format_pct.c\
ft_format_b.c\
ft_format_o.c\
ft_color.c\
ft_float.c\
ft_mult2.c\


OBJ = ft_format_csp.o\
ft_format_di.o\
ft_nan_inf.o\
ft_print_float.o\
ft_format_f.o\
ft_format_u.o\
ft_format_xx.o\
ft_check_add.o\
ft_check_char.o\
ft_convert.o\
ft_printf.o\
ft_ltoa.o\
ft_ftoa.o\
ft_utoa.o\
ft_dtoh.o\
ft_format_pct.o\
ft_format_b.o\
ft_format_o.o\
ft_color.o\
ft_float.o\
ft_mult2.o\

INCLUDE = ft_printf.h

.PHONY: all clean fclean re norme

$(NAME):
	@$(CC) $(FLAGS) -c $(SOURCES)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

all: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
