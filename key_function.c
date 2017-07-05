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

int		is_blocking(t_dpoint pos, t_wind *w)
{
	if (w->b.tab_int[(int)pos.z][(int)pos.x] == 1)
		return (1);
	return (0);
}

static void		keypress_function01(int keycode, t_wind *w, int percrotcam)
{
	t_dpoint		tmp;

		if (keycode == L_ARROW)
			w->cam.rot.y = rot_abs(w->cam.rot.y - percrotcam);
		else if (keycode == R_ARROW)
			w->cam.rot.y = rot_abs(w->cam.rot.y + percrotcam);
		else if (keycode == U_ARROW || keycode == D_ARROW)
		{
			if (keycode == U_ARROW)
			{
				tmp.x = w->cam.pos.x + cos(ft_degreetorad(w->cam.rot.y)) * MOVESPEED;
				tmp.z = w->cam.pos.z + sin(ft_degreetorad(w->cam.rot.y)) * MOVESPEED;
			}
			else if (keycode == D_ARROW)
			{
				tmp.x = w->cam.pos.x - cos(ft_degreetorad(w->cam.rot.y)) * MOVESPEED;
				tmp.z = w->cam.pos.z - sin(ft_degreetorad(w->cam.rot.y)) * MOVESPEED;
			}
			if (is_blocking(tmp, w) != 1)
			{
				w->cam.pos.x = tmp.x;
				w->cam.pos.z = tmp.z;
			}
		}
			/*else if (keycode == PAGE_U)
			w->rt.e.pos.z += 1;
		else if (keycode == PAGE_D)
			w->rt.e.pos.z -= 1;*/
		/*else if (keycode == NUM_U)
			w->rt.e.rot.x += percrotcam;
		else if (keycode == NUM_D)
			w->rt.e.rot.x -= percrotcam;*//*
		else if (keycode == NUM_R)
			w->cam.rot.y = rot_abs(w->cam.rot.y + percrotcam);
		else if (keycode == NUM_L)
			w->cam.rot.y = rot_abs(w->cam.rot.y - percrotcam);*/
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
