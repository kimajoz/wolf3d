/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_cast_single_ray_spr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:31:51 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/09 19:01:11 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				v_testspr(t_wind *w,  t_dpoint p,  t_dpoint dist, t_dpoint wall)
{
	if (w->w.tab_int_spr[(int)wall.y][(int)wall.x].num > 0)
	{
		dist = (t_dpoint){(p.x * MMS) - ((w->cam.pos.x + 0.5) * MMS),
			(p.y * MMS) - ((w->cam.pos.z + 0.5) * MMS), 0};
		w->w.block_distspr = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
		if ((!(ft_fiszero(w->w.block_distspr)) && w->w.block_distspr <
	w->w.olddist) && w->w.tab_int_spr[(int)wall.y][(int)wall.x].vis == 1)
			w->w.hit = p;
		if ((!(ft_fiszero(w->w.block_distspr)) && w->w.block_distspr <
	w->w.olddist) && w->w.tab_int_spr[(int)wall.y][(int)wall.x].vis != 1)
		{
			printf("dist current sprite: %.3f, wall: %.3f\n", w->w.block_distspr, w->w.olddist);
			w->w.hit2 = p;
			w->w.mindistspr = w->w.block_distspr;
			w->w.memdistspr = (t_dpoint){p.x - (w->cam.pos.x + 0.5), p.y -
			(w->cam.pos.z + 0.5), 0};
			w->w.block_distsprreal = sqrt(pow(w->w.memdistspr.x, 2) +
				pow(w->w.memdistspr.y, 2));
			w->w.tab_int_spr[(int)wall.y][(int)wall.x].vis = 1;
			w->w.sprnumb = w->w.tab_int_spr[(int)wall.y][(int)wall.x].num;
			return (1);
		}
	}
	return (0);
}


void			w_verticales_lines_check_spr(t_wind *w, double ray_angle,
		double right)
{
	t_dpoint	d;
	t_dpoint	p;
	t_dpoint	wall;
	t_dpoint	dist;

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
		if (v_testspr(w, p, dist, wall))
			break ;
		p.x += d.x;
		p.y += d.y;
	}
}

int				h_testspr(t_wind *w,  t_dpoint p,  t_dpoint dist, t_dpoint wall)
{
	if (w->w.tab_int_spr[(int)wall.y][(int)wall.x].num > 0)
	{
		dist = (t_dpoint){(p.x * MMS) - ((w->cam.pos.x + 0.5) * MMS),
			(p.y * MMS) - ((w->cam.pos.z + 0.5) * MMS), 0};
		w->w.block_distspr = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
		if (((!ft_fiszero(w->w.block_distspr)) && w->w.block_distspr <
	w->w.olddist) && w->w.tab_int_spr[(int)wall.y][(int)wall.x].vis == 1)
			w->w.hit = p;
		if (((!ft_fiszero(w->w.block_distspr)) && w->w.block_distspr <
	w->w.olddist) && w->w.tab_int_spr[(int)wall.y][(int)wall.x].vis != 1)
		{
			printf("dist current sprite: %.3f, wall: %.3f\n", w->w.block_distspr, w->w.olddist);
			w->w.hit2 = p;
			w->w.mindistspr = w->w.block_distspr;
			w->w.memdistspr  = (t_dpoint){p.x - (w->cam.pos.x + 0.5), p.y -
				(w->cam.pos.z + 0.5), 0};
			w->w.block_distsprreal = sqrt(pow(w->w.memdistspr.x, 2) +
				pow(w->w.memdistspr.y, 2));
			w->w.sprnumb = w->w.tab_int_spr[(int)wall.y][(int)wall.x].num;
			w->w.tab_int_spr[(int)wall.y][(int)wall.x].vis = 1;
			return (1);
		}
	}
	return (0);
}

void			w_horizontales_lines_check_spr(t_wind *w, double ray_angle,
		double up)
{
	t_dpoint	d;
	t_dpoint	p;
	t_dpoint	wall;
	t_dpoint	dist;

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
		if (h_testspr(w, p, dist, wall))
			break ;
		p.x += d.x;
		p.y += d.y;
	}
}

void			w_cast_single_ray_spr(t_wind *w, double ray_angle)
{
	double		right;
	double		up;

	w->w.distspr = 0;
	w->w.hit = (t_dpoint){0, 0, 0};
	ray_angle = ft_degreetorad(ray_angle);
	ray_angle = fmod(ray_angle, TWOPI);
	//printf("ray_angle spr:%.3f\n", ray_angle);
	right = (ray_angle > TWOPI * 0.75 || ray_angle < TWOPI * 0.25);
	up = (ray_angle < 0 || ray_angle > M_PI);
	w->w.dist = 0;
	w->w.mindistspr = 0;
	w_verticales_lines_check_spr(w, ray_angle, right);
	w_horizontales_lines_check_spr(w, ray_angle, up);
	if (!ft_fiszero(w->w.mindistspr))
		w->w.dist = w->w.block_distspr;
	//if (w->w.info.ray_minimap && w->w.info.tabinfo)
	w_print_radar_ray_hitwall(w, w->w.hit.x, w->w.hit.y, 0x0000FF);
	//if (w->w.sprite_angled > -(FOV / 2) && w->w.sprite_angled < (FOV / 2))
	w_print_radar_ray_hitwall(w, w->w.hit2.x, w->w.hit2.y, 0x00FFFF);
	if ((w->w.dist < w->w.olddist && !ft_fiszero(w->w.dist)) ||
		(ft_fiszero(w->w.olddist) && !ft_fiszero(w->w.dist)))
	{
		if (!ft_fiszero(w->w.dist))
			w_render_sprites(w);
	}
}
