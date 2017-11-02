/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:05:51 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/02 11:18:35 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
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
			if (w->b.tab_int[i / MMS][j / MMS] > 0)
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
	ft_putendl("wol 1");
	if (w->w.info.spr)
		w_clear_vis_sprites(w);
	ft_putendl("wol 2");
	game_cycle(w);
	ft_putendl("wol 4");
	w->w.timeimg = 0.01;
	if ((w->w.player.prevtimeoutimg + w->w.timeimg) < w->w.player.timeout ||
			!w->w.player.prevtimeoutimg)
	{
		ft_putendl("wol 5");
		w->w.player.prevtimeoutimg = w->w.player.timeout;
		w_clear_screen(w);
		//ft_putendl("wol 5a");
		if (w->w.info.bg)
			w_draw_background_color(w);
		//ft_putendl("wol 5b");
		if (w->w.info.tabinfo)
			init_minimap(w);
		//ft_putendl("wol 5c");
		w_cast_rays(w);
		//ft_putendl("wol 5d");
		if (w->w.info.spr)
			w_render_sprites(w);
		//ft_putendl("wol 5e");
		w_gun_fire(w);
		//ft_putendl("wol 5f");
		w_render_screen(w);
		//ft_putendl("wol 5g");
	}
	else if ((w->w.player.prevtimeoutimg + w->w.timeimg) > w->w.player.timeout
			&& w->w.player.prevtimeoutimg)
	{
		ft_putendl("wol 6 prev");
		w_render_screen(w);
		//ft_putendl("wol 6");
	}
	ft_putendl("wol 7");
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	//ft_putendl("wol 8");
	put_info(w);
	//ft_putendl("wol 9");
	return (0);
}
