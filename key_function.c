/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:01:12 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/03 11:37:12 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				is_blocking(t_dpoint pos, t_wind *w)
{
	printf("inside the map: %d\n", w_insidemap((int)pos.x, (int)pos.z, w));
	printf("pos.x: %d, pos.y:%d \n", (int)pos.x, (int)pos.z);
	printf("nbrtot_of_line: %d, nbr_elem_line:%d \n", w->b.nbrtot_of_line, w->b.nbr_elem_line[0]);
	if (w_insidemap((int)pos.x, (int)pos.z, w) &&
	(int)(w->b.tab_int[(int)pos.z][(int)pos.x]) > 0)
		return (1);
	return (0);
}

void			move(t_wind *w)
{
	t_dpoint	tmp;
	double		movestep;
	double		mult;

	tmp = (t_dpoint){0, 0, 0};
	mult = 1;
	movestep = mult * w->w.player.speed * w->w.player.movespeed;
	w->cam.rot.y = mult * ft_rot_fabs(w->cam.rot.y + w->w.player.dir *
			w->w.player.rotspeed);
	tmp.x = w->cam.pos.x + cos(ft_degreetorad(w->cam.rot.y)) * movestep;
	tmp.z = w->cam.pos.z + sin(ft_degreetorad(w->cam.rot.y)) * movestep;
	if (!is_blocking(tmp, w) &&
		((w->w.info.spr) ? (w_insidemap((int)tmp.x, (int)tmp.z, w) &&
		w->w.tab_int_spr[(int)tmp.z][(int)tmp.x].block
			!= 1) : 1))
	{
		w->cam.pos.x = tmp.x;
		w->cam.pos.z = tmp.z;
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
	{
		w->w.player.ammunition += 7;
		w->w.player.ammureload = 1;
		if (w->w.info.sound)
			w_play_music(w, w->lpth.fxguncocking, S_GUNCOKING, 0);
	}
}

static void		keypress_function02(int keycode, t_wind *w)
{
	if (keycode == KEY_1)
		w->w.info.raynumb = 60;
	else if (keycode == KEY_2)
	{
		w->w.info.raynumb = (w->w.info.raynumb < w->width) ?
			(w->w.info.raynumb - 10) : w->w.info.raynumb;
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
