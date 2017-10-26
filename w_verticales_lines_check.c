/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_verticales_lines_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:44:31 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/26 14:20:05 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			v_test(t_wind *w, t_dpoint *d, t_dpoint *p, t_dpoint *dist)
{
	while (p->x >= 0 && p->x < w->b.nbr_elem_line[0] && p->y >= 0 && p->y <
		w->b.nbrtot_of_line)
	{
		w->w.wall = (t_dpoint){floor(p->x + (w->w.right ? 0 : -1)),
			floor(p->y), 0};
		if (w->w.wall.x < 0 || w->w.wall.y < 0)
			break ;
		if ((w->b.tab_int[(int)w->w.wall.y][(int)w->w.wall.x] > 0))
		{
			*dist = (t_dpoint){(p->x * MMS) - (w->cam.pos.x * MMS),
				(p->y * MMS) - (w->cam.pos.z * MMS), 0};
			w->w.dist = sqrt(pow(dist->x, 2) + pow(dist->y, 2));
			w->w.hit = *p;
			w->w.tex_x = (!w->w.right) ? TEXWIDTH - (fmod(p->y, 1) * TEXWIDTH) :
				fmod(p->y, 1) * TEXWIDTH;
			w->w.textnumb = w->b.tab_int[(int)w->w.wall.y][(int)w->w.wall.x]
			- 1;
			w->w.color = (p->x < w->cam.pos.x) ? IC_FGREEN : IC_FBLUE;
			break ;
		}
		p->x += d->x;
		p->y += d->y;
	}
}

void			w_verticales_lines_check(t_wind *w, double ray_angle)
{
	t_dpoint	d;
	t_dpoint	p;
	t_dpoint	dist;

	w->w.slope = sin(ray_angle) / cos(ray_angle);
	d.x = w->w.right ? 1 : -1;
	d.y = (w->w.slope < 360) ? d.x * w->w.slope : 0;
	p.x = w->w.right ? ceil(w->cam.pos.x) : floor(w->cam.pos.x);
	p.y = (w->cam.pos.z) + (p.x - w->cam.pos.x) * w->w.slope;
	v_test(w, &d, &p, &dist);
}

int				h_test(t_wind *w, t_dpoint *p, t_dpoint *dist)
{
	if ((w->b.tab_int[(int)w->w.wall.y][(int)w->w.wall.x] > 0))
	{
		*dist = (t_dpoint){(p->x * MMS) - (w->cam.pos.x * MMS), (p->y * MMS)
			- (w->cam.pos.z * MMS), 0};
		w->w.block_dist = sqrt(pow(dist->x, 2) + pow(dist->y, 2));
		if (!w->w.dist ||
			(w->w.block_dist < w->w.dist && !ft_fiszero(w->w.block_dist)))
		{
			w->w.dist = w->w.block_dist;
			w->w.hit = *p;
			w->w.tex_x = (!w->w.up) ? TEXWIDTH - (fmod(p->x, 1) * TEXWIDTH) :
				fmod(p->x, 1) * TEXWIDTH;
			w->w.textnumb = w->b.tab_int[(int)w->w.wall.y][(int)w->w.wall.x]
				- 1;
			w->w.color = p->y < w->cam.pos.z ? IC_FYELLOW : IC_FPURPLE;
			return (1);
		}
	}
	return (0);
}

void			w_horizontales_lines_check(t_wind *w, double ray_angle)
{
	t_dpoint	d;
	t_dpoint	p;
	t_dpoint	dist;

	w->w.slope = cos(ray_angle) / sin(ray_angle);
	d.y = w->w.up ? -1 : 1;
	d.x = (w->w.slope < 360) ? (d.y * w->w.slope) : 0;
	p.y = w->w.up ? floor(w->cam.pos.z) : ceil(w->cam.pos.z);
	p.x = w->cam.pos.x + (p.y - w->cam.pos.z) * w->w.slope;
	while (p.x >= 0 && p.x < w->b.nbr_elem_line[0] && p.y >= 0 && p.y <
			w->b.nbrtot_of_line)
	{
		w->w.wall = (t_dpoint){floor(p.x), floor(p.y + (w->w.up ? -1 : 0)), 0};
		if (w->w.wall.x < 0 || w->w.wall.y < 0)
			break ;
		if (h_test(w, &p, &dist))
			break ;
		p.x += d.x;
		p.y += d.y;
	}
}
