/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_cast_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:05:19 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/04 18:31:27 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			w_draw_the_wall(t_wind *w, int i)
{
	double		projsliceh;
	t_point		p;
	t_point		pd;
	int			y;
	int			h;

	projsliceh = (CUBESIZE * w->w.player.fov) / w->w.dist;
	p = (t_point){(i * w->w.slicew), (w->height / 2) - (projsliceh / 2), 0};
	pd = (t_point){p.x, p.y + projsliceh, 0};
	p.x += w->w.marginw;
	pd.x += w->w.marginw;
	if (w->w.info.texture)
	{
		h = 0;
		y = p.y;
		while (y < pd.y)
		{
			h++;
			w->w.texY = (TEXHEIGHT / projsliceh) * h;
			w->w.color = getcolor(&w->w.text[w->w.textnumb], w->w.texX,
					w->w.texY);
			if (mlibx_dot_in_window(w, rint(p.x), y))
			{
				w->screen[y][(int)p.x].zdepth = w->w.dist;
				w->screen[y][(int)p.x].color = w->w.color;
			}
			y++;
		}
	}
	else
		mlibx_draw_pixel_line_int(p, pd, w, w->w.color);
}

void			w_verticales_lines_check(t_wind *w, double ray_angle,
		double right)
{
	t_dpoint	d;
	t_dpoint	p;
	t_dpoint	wall;
	t_dpoint	dist;

	w->w.foundh = 0;
	w->w.slope = sin(ray_angle) / cos(ray_angle);
	d.x = right ? 1 : -1;
	d.y = (w->w.slope < 360) ? d.x * w->w.slope : 0;
	p.x = right ? ceil(w->cam.pos.x) : floor(w->cam.pos.x);
	p.y = (w->cam.pos.z) + (p.x - w->cam.pos.x) * w->w.slope;
	while (p.x >= 0 && p.x < w->b.nbr_elem_line[0] && p.y >= 0 && p.y <
		w->b.nbrtot_of_line)
	{
		wall = (t_dpoint){floor(p.x + (right ? 0 : -1)), floor(p.y), 0};
		if (wall.x < 0 || wall.y < 0)
			break ;
		if ((w->b.tab_int[(int)wall.y][(int)wall.x] > 0))
		{
			dist = (t_dpoint){(p.x * MMS) - (w->cam.pos.x * MMS), (p.y * MMS) -
				(w->cam.pos.z * MMS), 0};
			w->w.dist = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
			w->w.hit = p;
			w->w.texX = (!right) ? TEXWIDTH - (fmod(p.y, 1) * TEXWIDTH) :
				fmod(p.y, 1) * TEXWIDTH;
			w->w.textnumb = w->b.tab_int[(int)wall.y][(int)wall.x] - 1;
			w->w.color = (p.x < w->cam.pos.x) ? IC_FGREEN : IC_FBLUE;
			w->w.side = 1;
			w->w.bolspr = 0;
			w->w.foundh = 1;
			break ;
		}
		p.x += d.x;
		p.y += d.y;
	}
}

void			w_horizontales_lines_check(t_wind *w, double ray_angle,
		double up)
{
	t_dpoint	d;
	t_dpoint	p;
	t_dpoint	wall;
	t_dpoint	dist;

	w->w.foundh = 0;
	w->w.slope = cos(ray_angle) / sin(ray_angle);
	d.y = up ? -1 : 1;
	d.x = (w->w.slope < 360) ? (d.y * w->w.slope) : 0;
	p.y = up ? floor(w->cam.pos.z) : ceil(w->cam.pos.z);
	p.x = w->cam.pos.x + (p.y - w->cam.pos.z) * w->w.slope;
	while (p.x >= 0 && p.x < w->b.nbr_elem_line[0] && p.y >= 0 && p.y <
			w->b.nbrtot_of_line)
	{
		wall = (t_dpoint){floor(p.x), floor(p.y + (up ? -1 : 0)), 0};
		if (wall.x < 0 || wall.y < 0)
			break ;
		if ((w->b.tab_int[(int)wall.y][(int)wall.x] > 0))
		{
			dist = (t_dpoint){(p.x * MMS) - (w->cam.pos.x * MMS), (p.y * MMS)
				- (w->cam.pos.z * MMS), 0};
			w->w.block_dist = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
			if (!w->w.dist ||
				(w->w.block_dist < w->w.dist && !ft_fiszero(w->w.block_dist)))
			{
				w->w.dist = w->w.block_dist;
				w->w.hit = p;
				w->w.texX = (!up) ? TEXWIDTH - (fmod(p.x, 1) * TEXWIDTH) :
					fmod(p.x, 1) * TEXWIDTH;
				w->w.textnumb = w->b.tab_int[(int)wall.y][(int)wall.x] - 1;
				w->w.color = p.y < w->cam.pos.z ? IC_FYELLOW : IC_FPURPLE;
				w->w.side = 0;
				w->w.bolspr = 0;
				w->w.foundh = 1;
				break ;
			}
		}
		p.x += d.x;
		p.y += d.y;
	}
}

void			w_cast_single_ray(t_wind *w, double ray_angle, int raynumb)
{
	double		right;
	double		up;

	w->w.dist = 0;
	w->w.distspr = 0;
	w->w.bolspr = 0;
	w->w.hit = (t_dpoint){0, 0, 0};
	ray_angle = ft_degreetorad(ray_angle);
	ray_angle = fmod(ray_angle, TWOPI);
	right = (ray_angle > TWOPI * 0.75 || ray_angle < TWOPI * 0.25);
	up = (ray_angle < 0 || ray_angle > M_PI);
	w_verticales_lines_check(w, ray_angle, right);
	w_horizontales_lines_check(w, ray_angle, up);
	if (w->w.dist)
	{
		if (w->w.info.ray_minimap && w->w.info.tabinfo)
			w_print_radar_ray_hitwall(w, w->w.hit.x, w->w.hit.y, 0x00FF00);
		w->w.dist = w->w.dist * cos(ft_degreetorad(w->w.correct_fisheyes));
		w->w.olddist = w->w.dist;
		w_draw_the_wall(w, raynumb);
	}
}

void			w_cast_rays(t_wind *w)
{
	int			i;
	double		angle;

	w->cam.vp.dist = ((w->cam.vp.w) / 2) / tan(ft_degreetorad(w->w.player.fov
		/ 2));
	w->cam.anglebetrays = (double)w->w.player.fov / (double)w->w.info.raynumb;
	w->w.slicew = w->width / w->w.info.raynumb;
	angle = w->cam.rot.y - (w->w.player.fov / 2);
	w->w.correct_fisheyes = w->w.player.fov / 2;
	i = 0;
	while (i < w->w.info.raynumb)
	{
		w->w.correct_fisheyes -= w->cam.anglebetrays;
		w_cast_single_ray(w, angle, i);
		angle += w->cam.anglebetrays;
		i++;
	}
	angle = w->cam.rot.y - (w->w.player.fov / 2);
	w->w.correct_fisheyes = w->w.player.fov / 2;
	i = 0;
	while (i < w->w.info.raynumb)
	{
		w->w.correct_fisheyes -= w->cam.anglebetrays;
		w_cast_single_ray_spr(w, angle);
		angle += w->cam.anglebetrays;
		i++;
	}
}
