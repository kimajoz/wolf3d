UNAME := $(shell uname)

NAME=wolf3d
SRC=	src/main.c \
		src/wolf3d.c \
		src/w_check_progstart.c \
		src/w_cast_rays.c \
		src/w_verticales_lines_check.c \
		src/w_print_radar_fov.c \
		src/w_draw_background_color.c \
		src/w_texture_walls.c \
		src/w_set_pxlfiletoimg.c \
		src/w_cast_single_ray_spr.c \
		src/w_render_sprites.c \
		src/w_clear_vis_sprites.c \
		src/w_set_pxl_spr_gunr.c \
		src/w_game_timer_cycle.c \
		src/w_game_over.c \
		src/w_play_music.c \
		src/w_gun_fire.c \
		src/w_get_configs.c \
		src/w_mlibx_draw_pixel_line.c \
		src/w_init_player_game.c \
		src/mlibx_putstring.c \
		src/rt_file.c \
		src/rt_parsing.c \
		src/w_create_spr_map.c \
		src/create_new_window.c \
		src/create_new_img.c \
		src/key_function.c \
		src/put_info.c \
		src/free_legend.c \
		src/expose_hook.c
OBJ=${SRC:.c=.o}

ifeq ($(UNAME), Darwin) # MAC
MINILIBX= make -C minilibx_macos
LIB= -lm -L libft -lft
LIB2= -L minilibx_macos -L/usr/local/lib/ -I/usr/local/include
LIB3= -lmlx -framework OpenGL -framework AppKit
FLAG= -Wall -Werror -Wextra
PTHREAD = -pthread
KEY= 1
endif
ifeq ($(UNAME), Linux) # LINUX
MINILIBX= make -C minilibx
LIB= -lm -L libft -lft
LIB2= -L minilibx -lmlx
LIB3= -L /usr/include/X11/ -lXext -lX11
FLAG= -Wall -Werror -Wextra
PTHREAD = -pthread -lrt
KEY= 2
endif

all: $(NAME)

$(NAME):	$(SRC)
	make -C libft
	$(MINILIBX)
	gcc $(FLAG) -o $(NAME) -g $(SRC) $(LIB) $(LIB2) $(LIB3) $(PTHREAD) -D MACROKEY=$(KEY)

clean:
	rm -rf $(OBJ)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
