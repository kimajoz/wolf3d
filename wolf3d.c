/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:17:23 by pbillett          #+#    #+#             */
/*   Updated: 2017/05/24 12:50:07 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			print_map(t_wind *w)
{
	int			i;
	int			j;

	i = 0;
	while (i < ((w->b.nbrtot_of_line + 1) * MINIMAPSCALE))
	{
		j = 0;
		while (j < (w->b.nbr_elem_line[(i / MINIMAPSCALE)] * MINIMAPSCALE))
		{
			if (w->b.tab_int[i/MINIMAPSCALE][j/MINIMAPSCALE] == 1)
				mlibx_draw_pixel(w, j, i, "0xFFFFFF");
			j++;
		}
		i++;
	}
	if (mlibx_dot_in_window(w, w->cam.pos.x * MINIMAPSCALE, w->cam.pos.z * MINIMAPSCALE) == 1)
		mlibx_draw_pixel(w, w->cam.pos.x * MINIMAPSCALE, w->cam.pos.z * MINIMAPSCALE, "0xFF0000");
	w_print_radar_ray(w, w->cam.pos.x * MINIMAPSCALE, w->cam.pos.z * MINIMAPSCALE, w->cam.rot.y, "0xFF0000");
	w_print_radar_fov(w, w->cam.pos.x * MINIMAPSCALE, w->cam.pos.z * MINIMAPSCALE, w->cam.rot.y, "0xFFFFFF");
}

int				check_wall(t_wind *w, t_point inter)
{
	//ft_putendl("check_wall");
	//printf("inter.x: %d, z:%d\n", inter.x, inter.z);
	if ((w->b.tab_int[inter.z][inter.x]) == 1)
	{
		ft_putendl("found!");
		return (1);
	}
	else
		ft_putendl("not found...");
	return (0);
}
/*
double			digital_differential_analyser(t_wind *w)
{
	double		t1;
	//double		t2;

	t1 = horizontal_detect(w);
	//t2 = vertical_detect(w);
	return (t1);
	//return((t1 < t2) ? t1 : t2);
}*/

void			wolf3d(t_wind *w)
{
	w_cast_rays(w);
	//digital_differential_analyser(w);
	print_map(w);
}
