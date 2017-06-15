UNAME := $(shell uname)

		#put_info.c \#
NAME=wolf3d
SRC=	main.c \
		wolf3d.c \
		rt_file.c \
		rt_parsing.c \
		create_new_window.c \
		create_new_img.c \
		key_function.c \
		expose_hook.c
OBJ=${SRC:.c=.o}

ifeq ($(UNAME), Darwin) # MAC
MINILIBX= make -C minilibx_macos
LIB= -lm -L libft -lft
LIB2= -L minilibx_macos -L/usr/local/lib/ -I/usr/local/include
LIB3= -lmlx -framework OpenGL -framework AppKit
FLAG= -Wall -Werror -Wextra
KEY= 1
endif
ifeq ($(UNAME), Linux) # LINUX
MINILIBX= make -C minilibx
LIB= -lm -L libft -lft
LIB2= -L minilibx -lmlx
LIB3= -L /usr/include/X11/ -lXext -lX11
FLAG= -Wall -Werror -Wextra
KEY= 2
endif

all: $(NAME)

$(NAME):	$(SRC)
	make -C libft
	$(MINILIBX)
	gcc $(FLAG) -o $(NAME) -g $(SRC) $(LIB) $(LIB2) $(LIB3) -D MACROKEY=$(KEY)

clean:
	rm -rf $(OBJ)
	make fclean -C libft

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
