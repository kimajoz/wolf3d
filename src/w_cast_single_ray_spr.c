/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_cast_single_ray_spr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:31:51 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/03 12:16:35 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			w_test_spr(t_dpoint wall, t_wind *w)
{
	if (w->w.tab_int_spr[(int)wall.y][(int)wall.x].num > 0 &&
			!w->w.tab_int_spr[(int)wall.y][(int)wall.x].vis)
	{
		w->w.tab_int_spr[(int)wall.y][(int)wall.x].vis = 1;
		w->w.visiblespr[w->w.sprnbvis] =
			w->w.tab_int_spr[(int)wall.y][(int)wall.x];
		w->w.bolspr = 1;
	}
}

void			w_verticales_lines_check_spr(t_wind *w, double ray_angle,
		double right)
{
	t_dpoint	d;
	t_dpoint	p;
	t_dpoint	wall;

	w->w.slope = sin(ray_angle) / cos(ray_angle);
	d.x = right ? 1 : -1;
	d.y = (w->w.slope < 360) ? d.x * w->w.slope : 0;
	p.x = right ? ceil(w->cam.pos.x + 0.5) : floor(w->cam.pos.x + 0.5);
	p.y = (w->cam.pos.z + 0.5) + (p.x - (w->cam.pos.x + 0.5)) * w->w.slope;
	while (p.x >= 0 && p.x < w->b.nbr_elem_line[0] && p.y >= 0 && p.y <
			w->b.nbrtot_of_line)
	{
		wall = (t_dpoint){floor(p.x + (right ? 0 : -1)), floor(p.y), 0};
		if (wall.x < 0 || wall.y < 0)
			break ;
		w_test_spr(wall, w);
		p.x += d.x;
		p.y += d.y;
	}
}

void			w_horizontales_lines_check_spr(t_wind *w, double ray_angle,
		double up)
{
	t_dpoint	d;
	t_dpoint	p;
	t_dpoint	wall;

	w->w.slope = cos(ray_angle) / sin(ray_angle);
	d.y = up ? -1 : 1;
	d.x = (w->w.slope < 360) ? (d.y * w->w.slope) : 0;
	p.y = up ? floor(w->cam.pos.z + 0.5) : ceil(w->cam.pos.z + 0.5);
	p.x = (w->cam.pos.x + 0.5) + (p.y - (w->cam.pos.z + 0.5)) * w->w.slope;
	while (p.x >= 0 && p.x < w->b.nbr_elem_line[0] && p.y >= 0 && p.y <
			w->b.nbrtot_of_line)
	{
		wall = (t_dpoint){floor(p.x), floor(p.y + (up ? -1 : 0)), 0};
		if (wall.x < 0 || wall.y < 0)
			break ;
		w_test_spr(wall, w);
		p.x += d.x;
		p.y += d.y;
	}
}

void			w_cast_single_ray_spr(t_wind *w, double ray_angle)
{
	double		right;
	double		up;

	w->w.bolspr = 0;
	w->w.hit = (t_dpoint){0, 0, 0};
	ray_angle = ft_degreetorad(ray_angle);
	ray_angle = fmod(ray_angle, TWOPI);
	right = (ray_angle > TWOPI * 0.75 || ray_angle < TWOPI * 0.25);
	up = (ray_angle < 0 || ray_angle > M_PI);
	w->w.dist = 0;
	w->w.mindistspr = 0;
	w_verticales_lines_check_spr(w, ray_angle, right);
	w_horizontales_lines_check_spr(w, ray_angle, up);
	if (w->w.bolspr)
		w->w.sprnbvis++;
}
