/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:01:12 by pbillett          #+#    #+#             */
/*   Updated: 2017/05/24 12:22:26 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define ROTABS(rot_z) ((rot_z >= 360 || rot_z <= -360) ? rot_z %= 360 : rot_z)
/*
static void		keypress_function01(int keycode, t_wind *w, int percrotcam)
{
	if (keycode == BACKSLASH && w->rt.ui_sel < 26)
		w->rt.ui_sel += 3;
	else if (keycode == EXCLAMMARK && w->rt.ui_sel > 20)
		w->rt.ui_sel -= 3;
	else if (keycode == KEY_1 && w->rt.speed_rt > 1)
		w->rt.speed_rt--;
	else if (keycode == KEY_2 && w->rt.speed_rt < 7)
		w->rt.speed_rt++;
	if (w->rt.ui_sel == 20)
	{
		if (keycode == L_ARROW)
			w->rt.e.pos.x -= 1;
		else if (keycode == R_ARROW)
			w->rt.e.pos.x += 1;
		else if (keycode == U_ARROW)
			w->rt.e.pos.y += 1;
		else if (keycode == D_ARROW)
			w->rt.e.pos.y -= 1;
		else if (keycode == PAGE_U)
			w->rt.e.pos.z += 1;
		else if (keycode == PAGE_D)
			w->rt.e.pos.z -= 1;
		else if (keycode == NUM_U)
			w->rt.e.rot.x += percrotcam;
		else if (keycode == NUM_D)
			w->rt.e.rot.x -= percrotcam;
		else if (keycode == NUM_R)
			w->rt.e.rot.y -= percrotcam;
		else if (keycode == NUM_L)
			w->rt.e.rot.y += percrotcam;
		else if (keycode == NUM_1)
			w->rt.e.rot.z += percrotcam;
		else if (keycode == NUM_3)
			w->rt.e.rot.z -= percrotcam;
	}
}*/

int				keypress_function(int keycode, t_wind *w)
{
	/*int			percrotobj;
	int			percrotcam;

	percrotobj = 15;
	percrotcam = 5;*/
	if (keycode == EXIT)
		exit(0);
	ROTABS(w->p.rot.z);
	//keypress_function01(keycode, w, percrotcam);
	/*if (keycode == KEY_S)
		rt_savefile(w);*/
	if (keycode != BACKSLASH && keycode != EXCLAMMARK && keycode != ZOOM_P && keycode != ZOOM_M)
	{
		mlx_destroy_image(w->mlx, w->img.ptr_img);
		create_new_img(w);
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	//put_info(w);
	return (0);
}
