/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_cast_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:05:19 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/09 17:56:16 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			w_draw_band_wall(t_wind *w, t_point *p, t_point *pd,
double projsliceh)
{
	int			y;
	int			h;

	h = 0;
	y = p->y;
	while (y < pd->y)
	{
		h++;
		w->w.texY = (TEXHEIGHT / projsliceh) * h;
		w->w.color = getcolor(&w->w.text[w->w.textnumb], w->w.texX,
				w->w.texY);
		if (mlibx_dot_in_window(w, rint(p->x), y))
		{
			w->screen[y][(int)p->x].zdepth = w->w.dist;
			w->screen[y][(int)p->x].color = w->w.color;
		}
		y++;
	}
}

void			w_draw_the_wall(t_wind *w, int i)
{
	double		projsliceh;
	t_point		p;
	t_point		pd;

	projsliceh = (CUBESIZE * w->w.player.fov) / w->w.dist;
	p = (t_point){(i * w->w.slicew), (w->height / 2) - (projsliceh / 2), 0};
	pd = (t_point){p.x, p.y + projsliceh, 0};
	p.x += w->w.marginw;
	pd.x += w->w.marginw;
	if (w->w.info.texture)
		w_draw_band_wall(w, &p, &pd, projsliceh);
	else
		w_mlibx_draw_pixel_line_int(p, pd, w, w->w.color);
}

void			w_cast_single_ray(t_wind *w, double ray_angle, int raynumb)
{
	w->w.dist = 0;
	w->w.distspr = 0;
	w->w.hit = (t_dpoint){0, 0, 0};
	ray_angle = ft_degreetorad(ray_angle);
	ray_angle = fmod(ray_angle, TWOPI);
	w->w.right = (ray_angle > TWOPI * 0.75 || ray_angle < TWOPI * 0.25);
	w->w.up = (ray_angle < 0 || ray_angle > M_PI);
	w_verticales_lines_check(w, ray_angle);
	w_horizontales_lines_check(w, ray_angle);
	if (w->w.dist)
	{
		if (w->w.info.ray_minimap && w->w.info.tabinfo)
			w_print_radar_ray_hitwall(w, w->w.hit.x, w->w.hit.y, IC_FGREEN);
		w->w.dist = w->w.dist * cos(ft_degreetorad(w->w.correct_fisheyes));
		w->w.olddist = w->w.dist;
		w_draw_the_wall(w, raynumb);
	}
}

void			w_cast_rays(t_wind *w)
{
	double		angle;

	w->w.distspr = 0;
	w->cam.vp.dist = ((w->cam.vp.w) / 2) / tan(ft_degreetorad(w->w.player.fov
		/ 2));
	w->cam.anglebetrays = (double)w->w.player.fov / (double)w->w.info.raynumb;
	w->w.slicew = w->width / w->w.info.raynumb;
	angle = w->cam.rot.y - (w->w.player.fov / 2);
	w->w.correct_fisheyes = w->w.player.fov / 2;
	w->w.curray = 0;
	while (w->w.curray < w->w.info.raynumb)
	{
		w->w.correct_fisheyes -= w->cam.anglebetrays;
		w_cast_single_ray(w, angle, w->w.curray);
		if (w->w.info.spr)
			w_cast_single_ray_spr(w, angle);
		angle += w->cam.anglebetrays;
		w->w.curray++;
	}
}
