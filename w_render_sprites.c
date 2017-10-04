/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_render_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:04:31 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/04 20:26:42 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w_clear_vis_sprites(t_wind *w)
{
	int		y;
	int		x;

	y = 0;
	while (y < w->b.nbrtot_of_line)
	{
		x = 0;
		while (x < w->b.nbr_elem_line[3])
			w->w.tab_int_spr[y][x++].vis = 0;
		y++;
	}
}

void		w_set_pxl_spr(int bx, int by, int size, t_wind *w)
{
	int		x;
	int		y;
	double	percx;
	double	percy;

	y = 0;
	while ((by + y) < (by + size))
	{
		x = 0;
		while ((bx + x) < (bx + size))
		{
			if (w->w.player.fire == 1 && w->w.player.ammunition)
				percx = (double)(x + (GUNW * 2.6)) / (double)size;
			else if (w->w.player.fire == 2 && w->w.player.ammunition)
				percx = (double)(x + (GUNW * 5)) / (double)size;
			else
				percx = (double)x / (double)size;
			percy = (double)y / (double)size;
			if (w->w.tmpgun)
				w->w.color = getcolor(&w->w.weapon[0], percx * GUNW, percy * GUNH);
			else
				w->w.color = getcolor(&w->w.sprite[w->w.sprnumb - 1].img, percx * 64, percy * 64);
			if (mlibx_dot_in_window(w, bx + x, by + y) && w->w.color != 0 && w->w.color != 16843008)
			{
				if (w->w.dist < w->screen[by + y][bx + x].zdepth &&
						!ft_fiszero(w->w.dist))
				{
					w->screen[by + y][bx + x].zdepth = w->w.dist;
					w->screen[by + y][bx + x].color = w->w.color;
				}
			}
			x++;
		}
		y++;
	}
}

void			w_calc_render_spr(t_wind *w)
{
	double		sprite_angle;
	int			sprite_angled;
	int			size;
	double		s_ytop;

	sprite_angle = fmod(atan2(w->w.memdistspr.y, w->w.memdistspr.x) -
		ft_degreetorad(w->cam.rot.y), TWOPI);
	printf("sprite_angle %.3f\n", sprite_angle);
	sprite_angled = (int)ft_radtodegree(sprite_angle);
	printf("sprite_angle degree %d\n", sprite_angled);
	//if (sprite_angled > -(FOV / 2) && sprite_angled < (FOV / 2))
	//{
		printf("angle ok! \n");
		size = w->cam.vp.dist / (cos(sprite_angle) * w->w.block_distsprreal);
		printf("w->cam.vp.dist %.3f\n", w->cam.vp.dist);
		printf("w->w.block_distsprreal %.3f\n", w->w.block_distsprreal);
		w->w.xtextp = tan(sprite_angle) * w->cam.vp.dist;
		printf("xtextp %.3f\n", w->w.xtextp);
		w->w.s_xleft = (((w->width) / 2) + w->w.xtextp) - (size / 2);
		//s_xleft = ((w->width - w->w.marginw) / 2) + xtextp - (size / 2) + w->w.marginw;
		s_ytop = (w->height - size) / 2;
		w_set_pxl_spr(w->w.s_xleft, s_ytop, size, w);
		printf("s_xleft: %.3f, s_ytop: %.3f size: %d\n", w->w.s_xleft, s_ytop, size);
	//}
	//else
		//printf("angle too small or too high! \n");
}

void		w_render_sprites(t_wind *w)
{
	int		y;
	int		x;

	y = 0;
	while (y < w->b.nbrtot_of_line)
	{
		x = 0;
		while (x < w->b.nbr_elem_line[3])
		{
			if (w->w.tab_int_spr[y][x].vis == 1)
				w_calc_render_spr(w);
			x++;
		}
		y++;
	}
}
