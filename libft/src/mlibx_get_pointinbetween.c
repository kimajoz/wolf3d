/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:42:59 by pbillett          #+#    #+#             */
/*   Updated: 2016/12/27 13:52:23 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int			dot_in_window(t_wind *w, int x, int y)
{
	if ((x > 0 && x < w->width) && (y > 0 && y < w->height))
		return (1);
	return (0);
}

t_point		move_to(t_wind *w, t_point p, int param)
{
	int		pyx;
	int		pxy;

	pyx = w->obj.gizt.p_y.x + w->obj.gizt.t.x;
	pxy = w->obj.gizt.p_x.y + w->obj.gizt.t.y;
	if (param == 0)
	{
		p.x = p.x - pyx;
		p.y = p.y - pxy;
		p.z = p.z;
	}
	else
	{
		p.x = p.x + pyx;
		p.y = p.y + pxy;
		p.z = p.z;
	}
	return (p);
}

static void	cond_getpoint_draw(t_wind *w, t_line v)
{
	char	*col;

	if ((w->p.dot == 1) && ((rint(v.x) == v.midx) && (rint(v.y) == v.midy)))
		draw_point(w, rint(v.x), rint(v.y), get_color(w, rint(v.z)));
	else if (w->obj.f.bolfill == 0 && w->p.graphic_mode == 4)
		draw_point(w, rint(v.x), rint(v.y), w->p.color.hexa_top);
	else if (w->p.color.hexa_bool)
		draw_point(w, rint(v.x), rint(v.y), w->p.color.hexa_default);
	else
	{
		col = get_color(w, rint(v.z));
		draw_point(w, rint(v.x), rint(v.y), col);
		ft_strdel(&col);
	}
}

int			get_pointinbetween(t_point point, t_point pointd, t_wind *w)
{
	t_line	v;

	v = convert_3ddot_to2dline(point, pointd, w);
	v = set_parameters_tline(v);
	if ((w->p.graphic_mode == 1) && (dot_in_window(w, rint(v.x), rint(v.y))))
		draw_point(w, (int)rint(v.x), (int)rint(v.y),
		get_color(w, w->img.point.z));
	else
	{
		while (rint(v.x) != v.xdest || rint(v.y) != v.ydest)
		{
			if (v.x != v.xdest)
				v.x += (v.sign_x * (v.diff_x / v.bigdiff));
			if (v.y != v.ydest)
				v.y += (v.sign_y * (v.diff_y / v.bigdiff));
			if (v.z != v.zdest)
				v.z += (v.sign_z * (v.diff_z / v.bigdiff));
			if (w->p.graphic_mode == 4 && w->obj.f.bol == 1)
				(w->obj.f.i++ == 0) ? (w->obj.f.beginpath = ft_pathinit(v)) :
		(w->obj.f.beginpath = ft_pathadd(w->obj.f.beginpath, ft_pathinit(v)));
			else if (dot_in_window(w, rint(v.x), rint(v.y)))
				cond_getpoint_draw(w, v);
		}
	}
	return (0);
}

int			draw_line(t_wind *w, t_point point, t_point pointd)
{
	w->p.rot.x += 45;
	point = move_to(w, point, 0);
	pointd = move_to(w, pointd, 0);
	point = matrice_rotation(point, w->p.rot, w->p.r_rot, w);
	pointd = matrice_rotation(pointd, w->p.rot, w->p.r_rot, w);
	point = move_to(w, point, 1);
	pointd = move_to(w, pointd, 1);
	w->p.rot.x -= 45;
	get_pointinbetween(point, pointd, w);
	return (0);
}
