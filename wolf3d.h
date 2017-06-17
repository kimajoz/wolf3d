#ifndef WOLF3D_H

# define WOLF3D_H

# define FOV		60
# define CUBESIZE	15
# define MAPSIZE	20
# define MOVINGSP	10

# if MACROKEY == 1
#  include "minilibx_macos/mlx.h"
# else
#  include "minilibx/mlx.h"
# endif
#include "libft/inc/libft.h"
#include "minilibx_struct.h"
#include "libft/inc/get_next_line.h"
#include "keymacro.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h> // A SUPPRIMER !

int				**rt_file(char *filename, int y, t_wind *w);
int				ft_check_parsing(char *filename);

void			put_info(t_wind *w);
int				prog(char *filename);
void			wolf3d(t_wind *w);

t_wind			create_new_window(char *title, int width, int height);
int				create_new_img(t_wind *w);

int				dot_in_window(t_wind *w, int x, int y);
int				keypress_function(int keycode, t_wind *w);
int				key_release_function(int keycode, t_wind *w);

int				expose_hook(t_wind *w);

#endif
