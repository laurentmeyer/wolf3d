CC = 		gcc
CFLAGS =	-g -Wall -Wextra -Werror
BINARY =	wolf3d
BUILDDIR =	builds
SOURCEDIR =	srcs
HEADERDIR = includes

SRCFILES =					\
			display.c		\
			exit.c			\
			init_assets.c	\
			init_display.c	\
			init_input.c	\
			init_ram.c		\
			init_render.c	\
			init_timer.c	\
			init_world.c	\
			input.c			\
			line.c			\
			main_loop.c		\
			main.c			\
			math.c			\
			raycast.c		\
			render.c		\
			timer.c			\
			transform.c		\
			world.c

LIBS =		ft						\
			mlx

LIBFT = 		./libft/

MINILIB = 		./mlx/

CCHEADERS = -I./$(HEADERDIR)				\
			-I$(LIBFT)/libft/includes		\
			-I$(LIBFT)/ft_printf/includes	\
			-I$(MINILIB)

CCLIBS = -L$(LIBFT) -lft			\
		 -L$(MINILIB) -lmlx

CCFRAMEWORKS = -framework AppKit -framework OpenGL

SOURCES = $(SRCFILES:%.c=$(SOURCEDIR)/%.c)
OBJECTS = $(SOURCES:$(SOURCEDIR)/%.c=$(BUILDDIR)/%.o)

.PHONY: all clean fclean re

all : $(BINARY)

$(BINARY) : $(OBJECTS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(MINILIB)
	$(CC) $(CCHEADERS) $(CCLIBS) $(OBJECTS) $(CCFRAMEWORKS) -o $(BINARY)

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CCHEADERS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(MINILIB) clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(BINARY)

re: fclean all
