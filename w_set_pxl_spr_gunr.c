/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_set_pxl_spr_gunr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:32:58 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/26 13:33:19 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w_set_pxl_spr_gun(int bx, int by, int size, t_wind *w)
{
	double	percx;
	double	percy;

	if (w->w.player.fire == 1 && w->w.player.ammunition)
		percx = (double)(w->w.pxl_x + (GUNW * 2.6)) / (double)size;
	else if (w->w.player.fire == 2 && w->w.player.ammunition)
		percx = (double)(w->w.pxl_x + (GUNW * 5)) / (double)size;
	else
		percx = (double)w->w.pxl_x / (double)size;
	percy = (double)w->w.pxl_y / (double)size;
	if (w->w.tmpgun)
		w->w.color = getcolor(&w->w.weapon[0], percx * GUNW, percy * GUNH);
	if (mlibx_dot_in_window(w, bx + w->w.pxl_x, by + w->w.pxl_y)
		&& w->w.color != 0 && w->w.color != 16843008)
	{
		w->screen[by + w->w.pxl_y][bx + w->w.pxl_x].zdepth = w->w.dist;
		w->screen[by + w->w.pxl_y][bx + w->w.pxl_x].color = w->w.color;
	}
}

void		w_set_pxl_spr_gunr(int bx, int by, int size, t_wind *w)
{
	w->w.pxl_y = 0;
	while ((by + w->w.pxl_y) < (by + size))
	{
		w->w.pxl_x = 0;
		while ((bx + w->w.pxl_x) < (bx + size))
		{
			w_set_pxl_spr_gun(bx, by, size, w);
			w->w.pxl_x++;
		}
		w->w.pxl_y++;
	}
}
