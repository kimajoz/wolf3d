/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:06:46 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/04 18:59:54 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define ROTABS(rot_z) ((rot_z >= 360 || rot_z <= -360) ? rot_z %= 360 : rot_z)

int			expose_hook(t_wind *w)
{
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img,
	w->img.x, w->img.y);
	put_info(w);
	return (0);
}

int			hook_render(t_wind *w)
{
	if (!w->w.player.kp.upwalk || w->w.player.fire != 0)
	{
		mlx_destroy_image(w->mlx, w->img.ptr_img);
		create_new_img(w);
	}
	return (0);
}

int			turntable(t_wind *w)
{
	if (w->p.turntable)
	{
		ROTABS(w->p.rot.z);
		w->p.rot.z += 5;
		mlx_destroy_image(w->mlx, w->img.ptr_img);
		create_new_img(w);
		mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x,
		w->img.y);
	}
	return (0);
}

int			key_release_function(int keycode, t_wind *w)
{
	if (keycode == R_ARROW || keycode == L_ARROW || keycode == U_ARROW ||
	keycode == D_ARROW)
		w->w.player.kp.upwalk = 1;
	if (keycode == SPACE)
		w->p.space_mousemove = 0;
	else if (keycode == R_ARROW || keycode == L_ARROW)
		w->w.player.dir = 0;
	else if (keycode == U_ARROW || keycode == D_ARROW)
		w->w.player.speed = 0;
	else if (keycode == SPACE)
		w->w.player.opendoor = 0;
	return (0);
}
