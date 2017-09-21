/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_gun_fire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 12:41:05 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/21 19:37:12 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w_gun_fire(t_wind *w)
{
	//ft_putendl("gun fire");
	//ft_putnbr(w->w.info.sound);
	w->w.dist = 0.2;
	w->w.tmpgun = 1;
	w_set_pxl_spr((w->width / 2) + (GUNW * 2), w->height - GUNH * 2, GUNH * 2, w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	w->w.dist = 0;
	w->w.tmpgun = 0;
}

void				w_gun_fire_loop(t_wind *w)
{
	ft_putendl("gun_fire_loop start");
	if (!w->w.player.ammureload)
		w->w.player.ammureload = 0;
	if (w->w.player.ammunition) // remove bullet
	{
		w->w.player.ammunition--; // remove bullet
		w->w.player.ammureload++; // until reload
		printf("reload: %d\n", w->w.player.ammureload);
		if (w->w.info.sound)
		{
			w_play_music(w, w->lpth.fxgunshot, "sounds/loops/gun-gunshot-01.wav", 0);
			pthread_join(w->lpth.fxgunshot, NULL);
		}
		if (w->w.player.ammureload > 7)
		{
			w->w.player.ammureload = 0;
			if (w->w.info.sound)
			{
				w_play_music(w, w->lpth.fxgunbulletfall, "sounds/loops/empty-bullet-shell-fall-01.wav", 0);
				pthread_join(w->lpth.fxgunbulletfall, NULL);
			}
		}
	}
	else if (!w->w.player.ammunition && w->w.info.sound) // No bullet please reload
	{
		w_play_music(w, w->lpth.fxgunbulletfall, "sounds/loops/empty-bullet-shell-fall-01.wav", 0);
		pthread_join(w->lpth.fxgunbulletfall, NULL);
	}
	//mlx_destroy_image(w->mlx, w->img.ptr_img);
	//create_new_img(w);
	//init_minimap(w);
	//mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	//put_info(w);
	//w_gun_fire(w);
	/*if (w->w.player.fire == 1)
		w->w.player.fire = 2;
	w_gun_fire(w);
	if (w->w.player.fire == 2)
		w->w.player.fire = 0;
	w_gun_fire(w);*/
	w->w.player.fire = 0;
	ft_putendl("gun_fire_loop end");
}
