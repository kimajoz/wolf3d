/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_parameters_tline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:10:43 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/10 15:15:08 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_sign(int first, int second)
{
	int		sign;

	if (first > second)
		sign = -1;
	else if (first == second)
		sign = 0;
	else
		sign = 1;
	return (sign);
}

static int	get_diff(int first, int second)
{
	int		i;

	i = 0;
	if (first > second)
		i = first - second;
	else
		i = second - first;
	return (i);
}

t_line		ft_conv_tpoint_to_tline_coord(t_point p)
{
	t_line	t;

	t.x = p.x;
	t.y = p.y;
	t.z = p.z;
	return (t);
}

t_line		convert_3ddot_to2dline(t_point point, t_point pointd, t_wind *w)
{
	t_line	v;

	v.x = point.x;
	v.xdest = pointd.x;
	if (w->obj.f.bolfill == 0)
	{
		v.y = point.y - point.z;
		v.z = w->p.color.z;
		v.ydest = pointd.y - pointd.z;
		v.zdest = w->p.color.zd;
	}
	else
	{
		v.y = point.y;
		v.z = point.z;
		v.ydest = pointd.y;
		v.zdest = pointd.z;
	}
	return (v);
}

t_line		set_parameters_tline(t_line v)
{
	v.midx = v.xdest + ((rint(v.x) - v.xdest) / 2);
	v.midy = v.ydest + ((rint(v.y) - v.ydest) / 2);
	v.sign_x = get_sign(v.x, v.xdest);
	v.sign_y = get_sign(v.y, v.ydest);
	v.sign_z = get_sign(v.z, v.zdest);
	v.diff_x = get_diff(v.x, v.xdest);
	v.diff_y = get_diff(v.y, v.ydest);
	v.diff_z = get_diff(v.z, v.zdest);
	if (v.diff_x > v.diff_y)
		v.bigdiff = v.diff_x;
	else if (v.diff_y > v.diff_x)
		v.bigdiff = v.diff_y;
	else
		v.bigdiff = v.diff_y;
	return (v);
}
