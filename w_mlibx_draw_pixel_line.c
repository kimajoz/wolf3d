/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_mlibx_draw_pixel_line.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:02:09 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/04 16:15:45 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft/inc/libft.h"

t_line		w_mlibx_set_parameters_tline(t_line v)
{
	v.midx = v.xdest + ((rint(v.x) - v.xdest) / 2);
	v.midy = v.ydest + ((rint(v.y) - v.ydest) / 2);
	v.sign_x = ft_iget_sign(v.x, v.xdest);
	v.sign_y = ft_iget_sign(v.y, v.ydest);
	v.diff_x = ft_iget_diff(v.x, v.xdest);
	v.diff_y = ft_iget_diff(v.y, v.ydest);
	if (v.diff_x > v.diff_y)
		v.bigdiff = v.diff_x;
	else if (v.diff_y > v.diff_x)
		v.bigdiff = v.diff_y;
	else
		v.bigdiff = v.diff_y;
	return (v);
}

void		w_mlibx_draw_pixel_line(t_point point, t_point pointd, t_wind *w,
int color)
{
	t_line	v;

	v.x = point.x;
	v.y = point.y;
	v.xdest = pointd.x;
	v.ydest = pointd.y;
	v = w_mlibx_set_parameters_tline(v);
	while (rint(v.x) != v.xdest || rint(v.y) != v.ydest)
	{
		if (v.x != v.xdest)
			v.x += (v.sign_x * (v.diff_x / v.bigdiff));
		if (v.y != v.ydest)
			v.y += (v.sign_y * (v.diff_y / v.bigdiff));
		if (mlibx_dot_in_window(w, rint(v.x), rint(v.y)))
		{
			w->screen[(int)rint(v.y)][(int)rint(v.x)].color = color;
			w->screen[(int)rint(v.y)][(int)rint(v.x)].zdepth = -10;
		}
	}
}

void		w_mlibx_draw_pixel_line_int(t_point point, t_point pointd,
t_wind *w, int color)
{
	t_line	v;

	v.x = point.x;
	v.y = point.y;
	v.xdest = pointd.x;
	v.ydest = pointd.y;
	v = w_mlibx_set_parameters_tline(v);
	while (rint(v.x) != v.xdest || rint(v.y) != v.ydest)
	{
		if (v.x != v.xdest)
			v.x += (v.sign_x * (v.diff_x / v.bigdiff));
		if (v.y != v.ydest)
			v.y += (v.sign_y * (v.diff_y / v.bigdiff));
		if (mlibx_dot_in_window(w, rint(v.x), rint(v.y)))
		{
			w->screen[(int)rint(v.y)][(int)rint(v.x)].zdepth = 1000;
			w->screen[(int)rint(v.y)][(int)rint(v.x)].color = color;
		}
	}
}

void		w_mlibx_draw_pixel(t_wind *w, int x, int y, int color)
{
	w->screen[y][x].zdepth = 0;
	w->screen[y][x].color = color;
}
