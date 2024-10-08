/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_print_radar_fov.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:05:35 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/02 15:20:29 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			w_print_radar_ray_hitwall(t_wind *w, double cx, double cy,
		int color)
{
	t_point		p;
	t_point		pd;

	p = (t_point){w->cam.pos.x * MMS, w->cam.pos.z * MMS, 0};
	pd = (t_point){cx * MMS, cy * MMS, 0};
	w_mlibx_draw_pixel_line(p, pd, w, color);
}

void			w_print_radar_ray(t_wind *w, double cx, double cy, int angle)
{
	t_point		p;
	t_point		pd;

	p = (t_point){cx * MMS, cy * MMS, 0};
	pd = (t_point){cos(ft_degreetorad(angle)) * RADARL + p.x,
		sin(ft_degreetorad(angle)) * RADARL + p.y, 0};
	w_mlibx_draw_pixel_line(p, pd, w, w->w.color_mray);
}

void			w_print_radar_fov(t_wind *w, double cx, double cy, int angle)
{
	t_point		p;
	t_point		pd;

	p = (t_point){cx * MMS, cy * MMS, 0};
	pd = (t_point){cos(ft_degreetorad(angle - (w->w.player.fov / 2))) * RADARL
		+ p.x, sin(ft_degreetorad(angle - (w->w.player.fov / 2))) * RADARL +
		p.y, 0};
	w_mlibx_draw_pixel_line(p, pd, w, w->w.color_mfov);
	pd = (t_point){cos(ft_degreetorad(angle + (w->w.player.fov / 2))) * RADARL
		+ p.x, sin(ft_degreetorad(angle + (w->w.player.fov / 2))) * RADARL +
		p.y, 0};
	w_mlibx_draw_pixel_line(p, pd, w, w->w.color_mfov);
}
