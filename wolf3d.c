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
# define MS 15
# define RADARL 100

void			print_radar_fov(t_wind *w, int cx, int cy, int angle)
{
	t_point		p;
	t_point		pd;

	p = (t_point){cx, cy, 0};
	pd = (t_point){cos(ft_degreetorad(angle)) * RADARL + p.x, sin(ft_degreetorad(angle)) * RADARL + p.y, 0};
	mlibx_draw_pixel_line(p, pd, w);
}

void			print_radar_hit_fov(t_wind *w, int x, int y)
{
	t_point		p;
	t_point		pd;

	p = (t_point){w->cam.pos.x, w->cam.pos.z, 0};
	pd = (t_point){x, y, 0};
	mlibx_draw_pixel_line(p, pd, w);
}

void			print_map(t_wind *w)
{
	int			i;
	int			j;

	i = 0;
	ft_putendl("print_map");
	/*p = (t_point){0, 0, 0};
	pd = (t_point){5, 300, 0};
	mlibx_draw_pixel_line(p, pd, w);*/
	while (i < ((w->b.nbrtot_of_line + 1) * MS))
	{
		j = 0;
		while (j < (w->b.nbr_elem_line[(i / MS)] * MS))
		{
			if (w->b.tab_int[i/MS][j/MS] == 1)
				mlibx_draw_pixel(w, j, i, "0xFFFFFF");
			j++;
		}
		i++;
	}
	mlibx_draw_pixel(w, w->cam.pos.x, w->cam.pos.z, "0xFF0000");
	print_radar_fov(w, w->cam.pos.x, w->cam.pos.z, w->cam.rot.y);
	ft_putendl("end print_map");
}

int				check_wall(t_wind *w, t_point inter)
{
	ft_putendl("check_wall");
	printf("inter.x: %d, z:%d\n", inter.x, inter.z);
	//ft_putlstnbr(w->b.tab_int[inter.z], w->b.nbr_elem_line[inter.z]);
	if ((w->b.tab_int[inter.z][inter.x]) == 1)
	{
		ft_putendl("found!");
		//print_radar_fov(w, inter.x, inter.z);
		return (1);
	}
	else
		ft_putendl("not found...");
	return (0);
}

/*
double			vertical_detect(t_wind *w)
{
	double		t;

	t = 100000000;
	return (t);
}*/

double			horizontal_detect(t_wind *w)
{
	int			Xa;
	int			Za;
	t_point		inter;

	// dir of the cam rays
	if (w->cam.rot.y >= 0 && w->cam.rot.z <= 180)
		Za = 1; // top dir
	else
		Za = - 1; // bot dir
	Xa = 1 / tan(w->cam.rot.y);
	printf("Xa: %d, Ya: %d\n", Xa, Za);


	// first inter coordonate
	if (w->cam.rot.y >= 0 && w->cam.rot.z <= 180)
		inter.z = ((w->cam.pos.z / CUBESIZE) * CUBESIZE) - 1;
	else
		inter.z = ((w->cam.pos.z / CUBESIZE) * CUBESIZE) + CUBESIZE;
	inter.x = w->cam.pos.x + (w->cam.pos.z - inter.z) / tan(w->cam.rot.y);
	printf("inter.x: %d, z: %d\n", inter.x, inter.z);


	if ((inter.z >= 0 && inter.z <= (CUBESIZE * MAPSIZE)) &&
		(inter.x >= 0 && inter.x <= (CUBESIZE * MAPSIZE)))
	{
		while (check_wall(w, inter) != 1)
		{
			inter.x += Xa;
			inter.z += Za;
			printf("old new inter.x: %d, z: %d\n", inter.x, inter.z);
		}
	}
	return (0);
}

double			digital_differential_analyser(t_wind *w)
{
	double		t1;
	//double		t2;

	t1 = horizontal_detect(w);
	//t2 = vertical_detect(w);
	return (t1);
	//return((t1 < t2) ? t1 : t2);
}

void			wolf3d(t_wind *w)
{
	//digital_differential_analyser(w);
	print_map(w);
}
