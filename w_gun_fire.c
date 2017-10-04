/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_gun_fire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 12:41:05 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/04 15:39:14 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				w_wait(t_wind *w, int timesec, int ifnum, int setnum)
{
	int		i;

	i = 0;
	if (w->w.player.fire == ifnum)
	{
		ft_putstr("fire ");
		ft_putnbr(ifnum);
		ft_putstr(" wait");
		while(i < timesec)
		{
			ft_putstr(".");
			i++;
		}
		w->w.player.fire = setnum;
	}
}

void		w_gun_fire(t_wind *w)
{
	if (w->w.player.fire == 2 || w->w.player.fire == 1)
	{
		ft_putendl("print gun fire image !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		ft_putnbr(w->w.player.fire);
		ft_putchar('\n');
	}
	w->w.dist = 0.2;
	w->w.tmpgun = 1;
	if (w->w.player.fire == 1)
		w_wait(w, 2, 1, 2);
	else if (w->w.player.fire == 2)
		w_wait(w, 2, 2, 0);
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
		if (w->w.info.sound)
			w_play_music(w, w->lpth.fxgunshot, "sounds/loops/gun-gunshot-01.wav", 0);
		if (w->w.player.ammureload > 7)
		{
			w->w.player.ammureload = 0;
			if (w->w.info.sound)
				w_play_music(w, w->lpth.fxgunbulletfall, "sounds/loops/empty-bullet-shell-fall-01.wav", 0);
		}
	}
	else if (!w->w.player.ammunition && w->w.info.sound) // No bullet please reload
		w_play_music(w, w->lpth.fxgunbulletfall, "sounds/loops/empty-bullet-shell-fall-01.wav", 0);
}
