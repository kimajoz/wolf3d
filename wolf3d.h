/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:06:00 by pbillett          #+#    #+#             */
/*   Updated: 2017/08/31 18:26:54 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H

# define WOLF3D_H

# define FOV 60
# define CUBESIZE 64
# define MOVESP 0.18
# define MMS 10
# define RADARL 100
# define RAYNUMB 600
# define TWOPI (M_PI * 2)
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define SPRWIDTH 64
# define SPRHEIGHT 64
# define MARGINIT 3
# define IC_DGREY 3355443//Rgb 51,51,51
# define IC_MGREY 7829367//Rgb 119,119,119
# define IC_FGREEN 65280//Rgb 0,255,0
# define IC_FBLUE 255//Rgb 0,0,255
# define IC_FYELLOW 16776960//Rgb 255,255,0
# define IC_FPURPLE 16711935//Rgb 255,0,255

# if MACROKEY == 1
#  include "minilibx_macos/mlx.h"
# else
#  include "minilibx/mlx.h"
# endif
# include "libft/inc/libft.h"
# include "minilibx_struct.h"
# include "libft/inc/get_next_line.h"
# include "keymacro.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h> // A SUPPRIMER !

int				rt_file(char *filename, int y, t_wind *w, int needed);
int				ft_check_parsing(char *filename);
int				ft_check_parsing_param(char *filename);
int				ft_print_error_type_parsing(int x, int y);
int				ft_count_lines(t_wind *w, char *filename);

void			put_info(t_wind *w);
int				prog(char *filename);
void			wolf3d(t_wind *w);
void			w_cast_rays(t_wind *w);
void			w_clear_vis_sprites(t_wind *w);
void			w_render_sprites(t_wind *w);
int				getcolor(t_img *img, int x, int y);

int				game_cycle(t_wind *w);
void			render_cycle(t_wind *w);
void			init_pthread(t_wind *w);

void			w_print_radar_ray(t_wind *w, double cx, double cy, int angle);
void			w_print_radar_fov(t_wind *w, double cx, double cy, int angle);
void			w_print_radar_ray_hitwall(t_wind *w, double cx, double cy,
		char *color);
void			w_draw_background_color(t_wind *w);

void			init_texture(t_wind *w);
void			init_sprites(t_wind *w);
void			draw_texture(t_wind *w, int n);
//void			move(t_wind *w, double time_delay);
void			move(t_wind *w);
//void			move(t_wind *w, struct timespec time_delay);
void			init_minimap(t_wind *w);
//void			init_screen_texture(t_wind *w);
//void			w_texture_walls(t_wind *w);

t_wind			create_new_window(char *title, int width, int height);
int				create_new_img(t_wind *w);

int				dot_in_window(t_wind *w, int x, int y);
int				keypress_function(int keycode, t_wind *w);
int				key_release_function(int keycode, t_wind *w);

int				expose_hook(t_wind *w);

#endif
