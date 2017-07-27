/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:01:12 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/21 09:32:54 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				rot_abs(int n)
{
	if (n >= 360)
		n %= 360;
	else if (n < 0)
		n = 360 + n;
	return (n);
}

int				is_blocking(t_dpoint pos, t_wind *w)
{
	if ((int)(w->b.tab_int[(int)pos.z][(int)pos.x]) > 0)
		return (1);
	return (0);
}

static void		keypress_function01(int keycode, t_wind *w, int percrotcam)
{
	t_dpoint	tmp;

	tmp = (t_dpoint){0, 0, 0};
	if (keycode == L_ARROW)
		w->cam.rot.y = rot_abs(w->cam.rot.y - percrotcam);
	else if (keycode == R_ARROW)
		w->cam.rot.y = rot_abs(w->cam.rot.y + percrotcam);
	else if (keycode == U_ARROW || keycode == D_ARROW)
	{
		if (keycode == U_ARROW)
		{
			tmp.x = w->cam.pos.x + cos(ft_degreetorad(w->cam.rot.y)) * MOVESP;
			tmp.z = w->cam.pos.z + sin(ft_degreetorad(w->cam.rot.y)) * MOVESP;
		}
		else if (keycode == D_ARROW)
		{
			tmp.x = w->cam.pos.x - cos(ft_degreetorad(w->cam.rot.y)) * MOVESP;
			tmp.z = w->cam.pos.z - sin(ft_degreetorad(w->cam.rot.y)) * MOVESP;
		}
		if (is_blocking(tmp, w) != 1)
		{
			w->cam.pos.x = tmp.x;
			w->cam.pos.z = tmp.z;
		}
	}
}

static void		keypress_function02(int keycode, t_wind *w)
{	if (keycode == KEY_1)
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
		w->w.info.sound = (w->w.info.sound) ? 0 : 1;
}

int				keypress_function(int keycode, t_wind *w)
{
	int			percrotcam;

	percrotcam = 5;
	if (keycode == EXIT)
		exit(0);
	rot_abs(w->cam.rot.y);
	keypress_function01(keycode, w, percrotcam);
	keypress_function02(keycode, w);
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	//w_texture_walls(w);
	put_info(w);
	return (0);
}
