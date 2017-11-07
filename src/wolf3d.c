/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:05:51 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 16:31:51 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"
#include <time.h>
#include <stdlib.h>

void				print_chara_minimap(t_wind *w)
{
	if (mlibx_dot_in_window(w, w->cam.pos.x * MMS, w->cam.pos.z * MMS) == 1)
		w_mlibx_draw_pixel(w, w->cam.pos.x * MMS, w->cam.pos.z * MMS, 0xFF0000);
	w_print_radar_ray(w, w->cam.pos.x, w->cam.pos.z, w->cam.rot.y);
	w_print_radar_fov(w, w->cam.pos.x, w->cam.pos.z, w->cam.rot.y);
}

void				init_minimap(t_wind *w)
{
	int			i;
	int			j;

	i = 0;
	while (i < (w->b.nbrtot_of_line * MMS))
	{
		j = 0;
		while (j < (w->b.nbr_elem_line[(i / MMS)] * MMS))
		{
			if (w->w.info.spr)
			{
				if (w->w.tab_int_spr[i / MMS][j / MMS].num == 1)
					w_mlibx_draw_pixel(w, j, i, 0xFF0000);
				else if (w->w.tab_int_spr[i / MMS][j / MMS].num == 4)
					w_mlibx_draw_pixel(w, j, i, 0x00FF00);
			}
			if (w_insidemap((int)(i / MMS), (int)(j / MMS), w) &&
			w->b.tab_int[i / MMS][j / MMS] > 0)
				w_mlibx_draw_pixel(w, j, i, 0xFFFFFF);
			j++;
		}
		i++;
	}
	print_chara_minimap(w);
}

void				tab_info(t_wind *w)
{
	if (!w->w.info.tabinfo)
	{
		w->w.marginw = 0;
		w->w.info.raynumb = w->width;
		w->w.player.fov = 70;
	}
	else
	{
		w->w.marginw = w->w.marginwfset;
		w->w.info.raynumb = w->width - w->w.marginw;
		w->w.player.fov = 50;
	}
}

int					game_cycle(t_wind *w)
{
	move(w);
	return (0);
}

int					wolf3d(t_wind *w)
{
	if (w->w.info.spr)
		w_clear_vis_sprites(w);
	game_cycle(w);
	w->w.timeimg = 0.01;
	if ((w->w.player.prevtimeoutimg + w->w.timeimg) < w->w.player.timeout ||
			!w->w.player.prevtimeoutimg)
	{
		w->w.player.prevtimeoutimg = w->w.player.timeout;
		w_clear_screen(w);
		if (w->w.info.bg)
			w_draw_background_color(w);
		if (w->w.info.tabinfo)
			init_minimap(w);
		w_cast_rays(w);
		if (w->w.info.spr)
			w_render_sprites(w);
		w_gun_fire(w);
		w_render_screen(w);
	}
	else if ((w->w.player.prevtimeoutimg + w->w.timeimg) > w->w.player.timeout
			&& w->w.player.prevtimeoutimg)
		w_render_screen(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	put_info(w);
	return (0);
}
