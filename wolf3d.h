#ifndef WOLF3D_H

# define WOLF3D_H
#include "libft/inc/libft.h"
# if MACROKEY == 1
#  include "minilibx_macos/mlx.h"
# else
#  include "minilibx/mlx.h"
# endif
#include "minilibx_struct.h"
#include "libft/inc/get_next_line.h"
#include "keymacro.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h> // A SUPPRIMER !

int				**rt_file(char *filename, int y, t_wind *w);
int				ft_check_parsing(char *filename);

void			put_info(t_wind *w);
int				wolf3d(char *filename);

t_wind			create_new_window(char *title, int width, int height);
int				create_new_img(t_wind *w);

int				dot_in_window(t_wind *w, int x, int y);
int				keypress_function(int keycode, t_wind *w);
int				key_release_function(int keycode, t_wind *w);

int				expose_hook(t_wind *w);

#endif
