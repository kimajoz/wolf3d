/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:29:21 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/15 14:31:00 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int				is_blocking(t_dpoint pos, t_wind *w)
{
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
