/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_game_timer_cycle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 20:19:22 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/03 12:19:13 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

void				w_draw_colored_bg(t_wind *w, int color)
{
	int				x;
	int				y;

	y = 0;
	while (y < w->height)
	{
		x = w->w.marginw;
		while (x < w->width)
		{
			w_mlibx_draw_pixel(w, x, y, color);
			x++;
		}
		y++;
	}
}

void				w_check_value_timer(t_wind *w, double millisec)
{
	if (w->w.player.win)
		w_win_level(w);
	if (w->w.player.gameover == 0)
		w->w.player.timeout = millisec / 1000;
	if (w->w.player.timeout > TIMEOUT_GAME && !w->w.player.win)
		w_game_over(w);
	check_win_game(w);
	if (w->w.player.fire == 1 && w->w.tmpgun == 0)
		w_gun_fire_loop(w);
	if ((w->w.player.health < 10 && w->w.player.gameover == 0) &&
			w->w.info.sound)
		w_play_music(w, w->lpth.fxheartb, S_HEARTBEAT, 0);
	ft_comment("w_check_value_timer");
}

void				*w_game_timer_cycle(void *data)
{
	clock_t			before;
	clock_t			diff;
	int				trigger;
	static double	millisec;
	t_wind			*w;

	w = (t_wind *)data;
	while (w->w.player.timeout <= TIMEOUT_GAME)
	{
		before = clock();
		w->w.tmpmsec = 0;
		trigger = 10;
		while (w->w.tmpmsec < trigger)
		{
			diff = clock() - before;
			w->w.tmpmsec = (double)diff * (double)1000 / (double)CLOCKS_PER_SEC;
		}
		millisec += w->w.tmpmsec;
		w_check_value_timer(w, millisec);
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	ft_comment("w_check_value_timer2");
	put_info(w);
	ft_comment("w_check_value_timer333");
	return (0);
}

void				w_play_chronotime(t_wind *w)
{
	pthread_create(&w->lpth.ptchrono, NULL, w_game_timer_cycle, (void*)w);
}
