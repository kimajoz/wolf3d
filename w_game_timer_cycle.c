/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_game_timer_cycle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 20:19:22 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/27 19:55:39 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

void	w_draw_colored_bg(t_wind *w, int color)
{
	int				x;
	int				y;

	y = 0;
	while (y < w->height)
	{
		x = w->w.marginw;
		while (x < w->width)
		{
			mlibx_draw_dot(w, x, y, color);
			x++;
		}
		y++;
	}
}

void			w_win_level(t_wind *w)
{
	w_draw_colored_bg(w, 0x0000cc);
	if (w->w.info.sound)
	{
		w_play_music(w, w->lpth.musicgameover, "sounds/loops/Casio-CZ-5000-Synth-Bass-C1.wav", 0);
		pthread_join(w->lpth.musicgameover, NULL);
	}
}

void			check_win_game(t_wind *w)
{
	//printf("win point.x: %d, point.y: %d\n", w->w.player.end_pos[0], w->w.player.end_pos[1]);
	//printf("current point.x: %d, point.y: %d\n", (int)w->cam.pos.x, (int)w->cam.pos.z);
	if (((int)w->cam.pos.x == w->w.player.end_pos[0]) &&
			((int)w->cam.pos.z == w->w.player.end_pos[1]) && !w->w.player.win)
	{
		ft_putendl("You win !");
		w->w.player.win = 1;
	}
}

void	w_game_over(t_wind *w)
{
	w->w.player.health = 0;
	w->w.player.totalscore = 0;
	w->w.player.gameover = 1;
	w_draw_colored_bg(w, 0xcc0000);
	if (w->w.info.sound)
	{
		w_play_music(w, w->lpth.musicgameover, "sounds/loops/Casio-CZ-5000-Synth-Bass-C1.wav", 0);
		pthread_join(w->lpth.musicgameover, NULL);
	}
}

void				*w_game_timer_cycle(void *data)
{
	clock_t			before;
	clock_t			diff;
	double			msec;
	int				trigger; // 10ms
	static double	millisec;
	t_wind			*w;

	w = (t_wind *)data;
	while (w->w.player.timeout <= TIMEOUT_GAME)
	{
		before = clock();
		msec = 0;
		trigger = 10;
		while (msec < trigger)
		{
			diff = clock() - before;
			msec = (double)diff * (double)1000 / (double)CLOCKS_PER_SEC;
		}
		millisec += msec;
		//printf("timeout sec:%d, milliseconde: %d, i:%d\n", (int)millisec/1000, (int)millisec, i); // Print of time
		if (w->w.player.win)
			w_win_level(w);
		if (w->w.player.gameover == 0) // https://stackoverflow.com/questions/17167949/how-to-use-timer-in-c
		{
			w->w.player.timeout = millisec/1000; // Set for wolf3d timeout
			//printf("");
		}
		if (w->w.player.timeout > TIMEOUT_GAME && !w->w.player.win)
		{
			ft_putendl("time out of game show gameover");
			w_game_over(w);
		}
		check_win_game(w);
		if (w->w.player.fire == 1 && w->w.tmpgun == 0)
			w_gun_fire_loop(w);
		if ((w->w.player.health < 10 && w->w.player.gameover == 0) && (w->w.info.sound))
		{
			w_play_music(w, w->lpth.fxheartb, "sounds/loops/Heartbeat.wav", 0);
			pthread_join(w->lpth.fxheartb, NULL);
		}
		if (!w->w.info.tabinfo)
		{
			//mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
			//put_info(w);
			//if (w->w.info.bg)
				//w_draw_background_color(w);
			//w->w.marginw = 0;
		}

	}
	ft_putendl("end of the while");
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	put_info(w);
	return (0);
}

void			w_play_chronotime(t_wind *w)
{
	ft_putendl("playchrono");
	//printf("playchrono: %.3f", w->w.dist);
	//while (w->w.player.timeout < TIMEOUT_GAME)
	pthread_create( &w->lpth.ptchrono, NULL, w_game_timer_cycle, (void*)w);
}
