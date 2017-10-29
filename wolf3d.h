/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:06:00 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/26 16:30:25 by pbillett         ###   ########.fr       */
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
# define TIMEOUT_GAME 1490
# define GUNW 84
# define GUNH 103
# define IC_DGREY 0x333333
# define IC_MGREY 0x777777
# define IC_FGREEN 0x00FF00
# define IC_FBLUE 0x0000FF
# define IC_FYELLOW 0xFFFF00
# define IC_FPURPLE 0xFF00FF
# define S_STARTL1 "sounds/loops/Casio-MT-45-16-Beat.wav"
# define S_FOOTSTEP "sounds/loops/footsteps-4_loop.wav"
# define S_GUNSHOT "sounds/loops/gun-gunshot-01.wav"
# define S_BULLETFALL "sounds/loops/empty-bullet-shell-fall-01.wav"
# define S_GUNCOKING "sounds/loops/gun-cocking-01.wav"
# define S_GAMEOVER "sounds/loops/Casio-CZ-5000-Synth-Bass-C1.wav"
# define S_GAMEWIN "sounds/loops/Alesis-Fusion-Bass-Loop.wav"
# define S_TELEPORTATION "sounds/loops/Yamaha-TG500-CH-Aah-C3.wav"
# define S_HORROR "sounds/loops/sounds/loops/M-Audio-Venom-Mysterio-C2.wav"
# define S_HEARTBEAT "sounds/loops/Heartbeat.wav"
# define S_ONSOUND "sounds/comedy_effect_steak.wav"
# define S_OFFSOUND "sounds/cartoon_sound_effects_pop.wav"

# if MACROKEY == 1
#  define OS 1
#  include "minilibx_macos/mlx.h"
# else
#  define OS 0
#  include "minilibx/mlx.h"
# endif

# include <pthread.h>
# include "libft/inc/libft.h"
# include "minilibx_struct.h"
# include "libft/inc/get_next_line.h"
# include "keymacro.h"
# include <math.h>
# include <stdlib.h>

int			w_check_progstart(t_wind *w, char *filename);
int			rt_file(char *filename, t_wind *w, int needed);
void		ft_check_parsing(t_wind *w, char *filename);
void		ft_check_parsing_param(char *filename);
int			ft_print_error_type_parsing(int x, int y);
int			ft_count_lines(t_wind *w, char *filename);
void		put_info(t_wind *w);
void		put_info_timeout(t_wind *w, int rightm, int bl);
void		*w_game_timer_cycle(void *data);
void		w_play_chronotime(t_wind *w);
int			w_play_music(t_wind *w, pthread_t addresspth, char *url, int loop);
void		w_sound_toggle(t_wind *w);
int			prog(char *filename);
int			wolf3d(t_wind *w);
void		w_cast_rays(t_wind *w);
void		w_cast_single_ray_spr(t_wind *w, double ray_angle);
void		w_clear_vis_sprites(t_wind *w);
void		w_render_sprites(t_wind *w);
void		w_set_pxl_spr_root(int bx, int by, int size, t_wind *w);
void		w_calc_render_spr(t_wind *w, t_sprite sprite);
void		w_gun_fire(t_wind *w);
void		w_gun_fire_loop(t_wind *w);
int			game_cycle(t_wind *w);
void		render_cycle(t_wind *w);
void		w_draw_colored_bg(t_wind *w, int color);
void		init_pthread(t_wind *w);
void		w_mlibx_draw_pixel_line_int(t_point point, t_point pointd,
		t_wind *w, int color);
void		w_mlibx_draw_pixel_line(t_point point, t_point pointd, t_wind *w,
		int color);
void		w_mlibx_draw_pixel(t_wind *w, int x, int y, int color);
void		w_print_radar_ray(t_wind *w, double cx, double cy, int angle);
void		w_print_radar_fov(t_wind *w, double cx, double cy, int angle);
void		w_print_radar_ray_hitwall(t_wind *w, double cx, double cy,
		int color);
void		w_draw_background_color(t_wind *w);
void		init_texture(t_wind *w);
void		init_sprites(t_wind *w);
void		init_guns(t_wind *w);
void		draw_texture(t_wind *w, int n);
void		move(t_wind *w);
void		init_minimap(t_wind *w);
t_wind		create_new_window(char *title, int width, int height);
int			create_new_img(t_wind *w);
int			dot_in_window(t_wind *w, int x, int y);
int			keypress_function(int keycode, t_wind *w);
int			key_release_function(int keycode, t_wind *w);
int			expose_hook(t_wind *w);
int			hook_render(t_wind *w);
void		mlibx_putstring(char *s, int l, int c, t_wind *w);
void		w_win_level(t_wind *w);
void		check_win_game(t_wind *w);
void		w_game_over(t_wind *w);
int			getcolor(t_img *img, int x, int y);
void		w_init_player_pos(t_wind *w);
void		w_init_player_game(t_wind *w);
void		w_init_screen(t_wind *w);
void		w_clear_screen(t_wind *w);
void		w_render_screen(t_wind *w);
int			set_spr_to_prog(int fd, char *filename, t_wind *w);
void		w_set_pxlfiletoimg(t_wind *w, int max, char **lst, void *d);
void		w_verticales_lines_check(t_wind *w, double ray_angle);
void		w_horizontales_lines_check(t_wind *w, double ray_angle);
void		w_set_pxl_spr_gunr(int bx, int by, int size, t_wind *w);
void		free_tablst(char **tab);

#endif
