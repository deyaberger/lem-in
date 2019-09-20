#
#

NOM=libmlx.a
SRCM= mlx_new_window.m mlx_init_loop.m mlx_new_image.m
SRCC= mlx_shaders.c mlx_xpm.c mlx_int_str_to_wordtab.c
OBJ1= mlx_shaders.o mlx_xpm.o mlx_int_str_to_wordtab.o
OBJ= mlx_new_window.o mlx_init_loop.o mlx_new_image.o
CFLAGS+=-O2

all: $(NOM)

$(NOM):
	@cc $(CFLAGS) -c $(SRCM)
	@cc $(CFLAGS) -c $(SRCC)
	@ar -rc $(NOM) $(OBJ)
	@ranlib $(NOM)

clean:
	@rm -f $(NOM) $(OBJ1) *~
	@rm -f $(NOM) $(OBJ) *~
	@rm -f mlx_app

re: clean all
