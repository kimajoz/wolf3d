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

int		rot_abs(int n)
{
	if (n >= 360)
		n %= 360;
	else if (n < 0)
		n = 360 + n;
	return (n);
}

static void		keypress_function01(int keycode, t_wind *w, int percrotcam)
{
		if (keycode == L_ARROW)
			w->cam.pos.x -= 1;
		else if (keycode == R_ARROW)
			w->cam.pos.x += 1;
		else if (keycode == U_ARROW)
			w->cam.pos.z -= 1;
		else if (keycode == D_ARROW)
			w->cam.pos.z += 1;
		/*else if (keycode == PAGE_U)
			w->rt.e.pos.z += 1;
		else if (keycode == PAGE_D)
			w->rt.e.pos.z -= 1;*/
		/*else if (keycode == NUM_U)
			w->rt.e.rot.x += percrotcam;
		else if (keycode == NUM_D)
			w->rt.e.rot.x -= percrotcam;*/
		else if (keycode == NUM_R)
			w->cam.rot.y = rot_abs(w->cam.rot.y + percrotcam);
		else if (keycode == NUM_L)
			w->cam.rot.y = rot_abs(w->cam.rot.y - percrotcam);
		/*
		else if (keycode == NUM_1)
			w->rt.e.rot.z += percrotcam;
		else if (keycode == NUM_3)
			w->rt.e.rot.z -= percrotcam;*/
}

int				keypress_function(int keycode, t_wind *w)
{
	//int			percrotobj;
	int			percrotcam;

	//percrotobj = 15;
	percrotcam = 5;
	if (keycode == EXIT)
		exit(0);
	//ft_putnbr(keycode);
	rot_abs(w->cam.rot.y);
	keypress_function01(keycode, w, percrotcam);
	/*if (keycode == KEY_S)
		rt_savefile(w);*/
	if (keycode != BACKSLASH && keycode != EXCLAMMARK && keycode != ZOOM_P && keycode != ZOOM_M)
	{
		mlx_destroy_image(w->mlx, w->img.ptr_img);
		create_new_img(w);
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	put_info(w);
	return (0);
}
