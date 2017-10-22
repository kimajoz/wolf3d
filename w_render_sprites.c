/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_render_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:04:31 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/09 19:12:30 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w_clear_vis_sprites2dspr_list(t_wind *w)
{
	int		i;

	i = 0;
	free(w->w.oldvisiblespr);
	w->w.oldvisiblespr = NULL;
	w->w.oldvisiblespr = malloc(w->w.nbtotsprprog * sizeof(t_sprite));
	while (i < w->w.sprnbvis)
	{
		w->w.oldvisiblespr[i] = w->w.visiblespr[i];
		w->w.oldvisiblespr[i].vis = 0;
		i++;
	}
	w->w.sprnbvis = 0;
	//ft_putendl("before free");
	free(w->w.visiblespr);
	//ft_putendl("after free");
	w->w.visiblespr = NULL;
	//ft_putendl("after null");
	w->w.visiblespr = malloc(w->w.nbtotsprprog * sizeof(t_sprite));
}

void		w_clear_vis_sprites(t_wind *w)
{
	//ft_putendl("after null creation");
	int		y;
	int		x;

	// We clear grid, then we clear list:
	y = 0;
	while (y < w->b.nbrtot_of_line)
	{
		x = 0;
		while (x < w->b.nbr_elem_line[3])
			w->w.tab_int_spr[y][x++].vis = 0;
		y++;
	}
	w_clear_vis_sprites2dspr_list(w);
}

void		w_set_pxl_spr(int bx, int by, int size, t_wind *w)
{
	double	percx;
	double	percy;
	
	//ft_putendl();
	if (w->w.player.fire == 1 && w->w.player.ammunition)
		percx = (double)(w->w.pxl_x + (GUNW * 2.6)) / (double)size;
	else if (w->w.player.fire == 2 && w->w.player.ammunition)
		percx = (double)(w->w.pxl_x + (GUNW * 5)) / (double)size;
	else
		percx = (double)w->w.pxl_x / (double)size;
	percy = (double)w->w.pxl_y / (double)size;
	if (w->w.tmpgun)
		w->w.color = getcolor(&w->w.weapon[0], percx * GUNW, percy * GUNH);
	else
		w->w.color = getcolor(&w->w.sprite[w->w.sprnumb - 1].img, percx * 64, percy * 64);
	if (mlibx_dot_in_window(w, bx + w->w.pxl_x, by + w->w.pxl_y) && w->w.color != 0 && w->w.color != 16843008)
	{
		//if (!w->w.tmpgun)
			//ft_putendl("set inside");
		/*if (w->w.dist < w->screen[by + w->w.pxl_y][bx + w->w.pxl_x].zdepth &&
				!ft_fiszero(w->w.dist))
		{*/
			w->screen[by + w->w.pxl_y][bx + w->w.pxl_x].zdepth = w->w.dist;
			w->screen[by + w->w.pxl_y][bx + w->w.pxl_x].color = w->w.color;
		//}
	}
}

void		w_set_pxl_spr_root(int bx, int by, int size, t_wind *w)
{
	w->w.pxl_y = 0;
	while ((by + w->w.pxl_y) < (by + size))
	{
		w->w.pxl_x = 0;
		while ((bx + w->w.pxl_x) < (bx + size))
		{
			w_set_pxl_spr(bx, by, size, w);
			w->w.pxl_x++;
		}
		w->w.pxl_y++;
	}
}

void		w_calc_render_spr(t_wind *w, t_sprite sprite)
{
	double	sprite_angle;
	int		size;
	double	s_ytop;
	double	dx;
	double	dy;

	w->w.sprnumb = sprite.num;
	ft_putendl("01");
	// https://dev.opera.com/articles/3d-games-with-canvas-and-raycasting-part-2/
	// Translate position to viewer space
	dx = sprite.posx + 0.5 - w->cam.pos.x;
	dy = sprite.posy + 0.5 - w->cam.pos.z;

	//ft_putendl("02");
	// Distance to sprite
	w->w.block_distsprreal = sqrt(pow(dx, 2) + pow(dy, 2));
	printf("block_distsprreal: %.3f\n", w->w.block_distsprreal);

	//ft_putendl("03");
	// Sprite angle relative to viewing angle
	sprite_angle = fmod(atan2(dy, dx) - ft_degreetorad(w->cam.rot.y), TWOPI);


	//ft_putendl("04");
	printf("sprite_angle %.3f\n", sprite_angle);
	w->w.sprite_angled = (int)ft_radtodegree(sprite_angle);
	printf("sprite_angle degree %d\n", w->w.sprite_angled);
	//if (w->w.sprite_angled > -(FOV / 2) && w->w.sprite_angled < (FOV / 2))
	//{
		printf("numero du sprite a afficher: %d\n", sprite.num);
		//printf("angle ok! \n");
		//ft_putendl("05");
		size = w->cam.vp.dist / (cos(sprite_angle) * w->w.block_distsprreal);
		//printf("w->cam.vp.dist %.3f\n", w->cam.vp.dist);
		//printf("w->w.block_distsprreal %.3f\n", w->w.block_distsprreal);
		//printf("w->cam.vp.dist %.3f\n", w->cam.vp.dist);
		printf("size: %d\n", size);
		w->w.xtextp = tan(sprite_angle) * w->cam.vp.dist;
		//if (w->w.xtextp < 0)
			//w->w.xtextp = -w->w.xtextp;
		printf("xtextp %.3f\n", w->w.xtextp);
		//w->w.s_xleft = ((w->width) / 2) - (size / 2) + w->w.xtextp;
		w->w.s_xleft = ((w->width - w->w.marginw) / 2) + w->w.xtextp - (size / 2) + w->w.marginw;
		//ft_putendl("08");
		s_ytop = (w->height - size) / 2;
		w_set_pxl_spr_root(w->w.s_xleft, s_ytop, size, w);
		//ft_putendl("10");
		printf("s_xleft: %.3f, s_ytop: %.3f size: %d\n", w->w.s_xleft, s_ytop, size);
	//}
}

void			w_render_sprites(t_wind *w)
{
	int			i;

	i = 0;
	printf("total sprite to display: %d\n", w->w.sprnbvis);
	while (i < w->w.sprnbvis)
	{
		w_calc_render_spr(w, w->w.visiblespr[i]);
		i++;
	}
}

/*void		w_render_sprites(t_wind *w)
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
}*/
