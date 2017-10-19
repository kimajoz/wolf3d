/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_gun_fire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 12:41:05 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/04 18:56:16 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			w_wait(t_wind *w, int timesec, int ifnum, int setnum)
{
	int		i;

	i = 0;
	if (w->w.player.fire == ifnum)
	{
		while (i < timesec)
			i++;
		w->w.player.fire = setnum;
	}
}

void				w_gun_fire(t_wind *w)
{
	w->w.dist = 0.2;
	w->w.tmpgun = 1;
	if (w->w.player.fire == 1)
		w_wait(w, 2, 1, 2);
	else if (w->w.player.fire == 2)
		w_wait(w, 2, 2, 0);
	w_set_pxl_spr_root((w->width / 2) + (GUNW * 2), w->height - GUNH * 2, GUNH * 2,
		w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	w->w.dist = 0;
	w->w.tmpgun = 0;
}

void				w_gun_fire_loop(t_wind *w)
{
	ft_putendl("gun fire loop");
	ft_putstr("reload:");
	ft_putnbr(w->w.player.ammureload);
	ft_putstr("\n");
	w->w.tmpgun = 1;
	if (!w->w.player.ammureload)
		w->w.player.ammureload = 1;
	if (w->w.player.ammunition)
	{
		w->w.player.ammunition--;
		w->w.player.ammureload++;
		if (w->w.info.sound)
			w_play_music(w, w->lpth.fxgunshot, S_GUNSHOT, 0);
		if (w->w.player.ammureload > 6)
		{
			w->w.player.ammureload = 1;
			if (w->w.info.sound)
				w_play_music(w, w->lpth.fxgunbulletfall, S_BULLETFALL, 0);
		}
	}
	else if (!w->w.player.ammunition && w->w.info.sound)
		w_play_music(w, w->lpth.fxgunbulletfall, S_BULLETFALL, 0);
}
