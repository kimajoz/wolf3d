/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:01:12 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/15 14:30:20 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			w_reload_gun(t_wind *w)
{
	if (w->w.player.ammunition < 17)
	{
		w->w.player.ammunition += 7;
		w->w.player.ammureload = 1;
		if (w->w.info.sound)
			w_play_music(w, w->lpth.fxguncocking, S_GUNCOKING, 0);
	}
}

static void		keypress_function01(int keycode, t_wind *w)
{
	if (keycode == U_ARROW || keycode == D_ARROW || keycode == R_ARROW ||
			keycode == L_ARROW)
		w->w.player.kp.upwalk = 0;
	if (((keycode == U_ARROW) || (keycode == D_ARROW)) && w->w.info.sound)
		w_play_music(w, w->lpth.fxwalk, S_FOOTSTEP, 0);
	if (keycode == L_ARROW)
		w->w.player.dir = -1;
	else if (keycode == R_ARROW)
		w->w.player.dir = 1;
	else if (keycode == U_ARROW)
		w->w.player.speed = 1;
	else if (keycode == D_ARROW)
		w->w.player.speed = -1;
	else if (keycode == SPACE)
		w->w.player.opendoor = 1;
	else if (keycode == CTRL_R)
		w->w.player.fire = 1;
	else if (keycode == KEY_R)
		w_reload_gun(w);
}

static void		keypress_function02(int keycode, t_wind *w)
{
	if (keycode == KEY_1)
		w->w.info.raynumb = 60;
	else if (keycode == KEY_2)
	{
		w->w.info.raynumb = (w->w.info.raynumb < w->width &&
		w->w.info.raynumb > 10) ? (w->w.info.raynumb - 10) : w->w.info.raynumb;
	}
	else if (keycode == KEY_3)
	{
		w->w.info.raynumb = (w->w.info.raynumb < w->width) ?
			(w->w.info.raynumb + 10) : w->w.info.raynumb;
	}
	else if (keycode == KEY_4)
		w->w.info.raynumb = 600;
	else if (keycode == KEY_5)
		w->w.info.ray_minimap = (w->w.info.ray_minimap) ? 0 : 1;
	else if (keycode == KEY_6)
		w->w.info.bg = (w->w.info.bg) ? 0 : 1;
	else if (keycode == KEY_7)
		w->w.info.texture = (w->w.info.texture) ? 0 : 1;
	else if (keycode == KEY_8)
		w_sound_toggle(w);
	else if (keycode == TAB_L)
		w->w.info.tabinfo = (w->w.info.tabinfo) ? 0 : 1;
}

int				keypress_function(int keycode, t_wind *w)
{
	if (keycode == EXIT)
		exit(0);
	if (!w->w.player.gameover && !w->w.player.win)
	{
		keypress_function01(keycode, w);
		keypress_function02(keycode, w);
		mlx_destroy_image(w->mlx, w->img.ptr_img);
		create_new_img(w);
	}
	return (0);
}
