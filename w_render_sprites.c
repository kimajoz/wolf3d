/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_render_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:04:31 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/26 13:37:38 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			w_set_pxl_spr(int bx, int by, int size, t_wind *w)
{
	double		percx;
	double		percy;

	percx = (double)w->w.pxl_x / (double)size;
	percy = (double)w->w.pxl_y / (double)size;
	w->w.color = getcolor(&w->w.sprite[w->w.sprnumb - 1].img, percx * 64,
			percy * 64);
	if (mlibx_dot_in_window(w, bx + w->w.pxl_x, by + w->w.pxl_y) &&
			w->w.color != 0 && w->w.color != 16843008)
	{
		if (w->w.mindistspr < w->screen[by + w->w.pxl_y][bx + w->w.pxl_x]
	.zdepth && !ft_fiszero(w->w.block_distsprreal) && (bx + w->w.pxl_x) >
	w->w.marginw)
		{
			w->screen[by + w->w.pxl_y][bx + w->w.pxl_x].zdepth = w->w.dist;
			w->screen[by + w->w.pxl_y][bx + w->w.pxl_x].color = w->w.color;
		}
	}
}

void			w_set_pxl_spr_root(int bx, int by, int size, t_wind *w)
{
	w->w.pxl_y = 0;
	while ((by + w->w.pxl_y) < (by + size))
	{
		w->w.pxl_x = 0;
		while ((bx + w->w.pxl_x) < (bx + size))
		{
			w_set_pxl_spr(bx, by, size, w);
			w->w.pxl_x++;
		}
		w->w.pxl_y++;
	}
}

void			w_calc_render_spr(t_wind *w, t_sprite sprite)
{
	double		sprite_angle;
	int			size;
	double		s_ytop;
	t_dpoint	d;
	t_dpoint	m;

	w->w.sprnumb = sprite.num;
	d.x = sprite.posx + 0.5 - w->cam.pos.x;
	d.y = sprite.posy + 0.5 - w->cam.pos.z;
	w->w.block_distsprreal = sqrt(pow(d.x, 2) + pow(d.y, 2));
	m = (t_dpoint){(sprite.posx * MMS) - ((w->cam.pos.x + 0.5) * MMS),
	(sprite.posy * MMS) - ((w->cam.pos.z + 0.5) * MMS), 0};
	w->w.mindistspr = sqrt(pow(m.x, 2) + pow(m.y, 2));
	sprite_angle = fmod(atan2(d.y, d.x) - ft_degreetorad(w->cam.rot.y), TWOPI);
	w->w.sprite_angled = (int)ft_radtodegree(sprite_angle);
	size = w->cam.vp.dist / (cos(sprite_angle) * w->w.block_distsprreal);
	w->w.xtextp = tan(sprite_angle) * w->cam.vp.dist;
	w->w.s_xleft = ((w->width - w->w.marginw) / 2) + w->w.xtextp - (size / 2) +
		w->w.marginw;
	s_ytop = (w->height - size) / 2;
	w_set_pxl_spr_root(w->w.s_xleft, s_ytop, size, w);
}

void			w_render_sprites(t_wind *w)
{
	int			i;

	i = 0;
	while (i < w->w.sprnbvis)
	{
		w_calc_render_spr(w, w->w.visiblespr[i]);
		i++;
	}
}
