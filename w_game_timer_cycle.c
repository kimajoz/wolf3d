/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_game_timer_cycle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 20:19:22 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/14 20:44:46 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

void	w_game_over_draw_bg(t_wind *w)
{
	int				x;
	int				y;

	y = 0;
	while (y < w->height)
	{
		x = w->w.marginw;
		while (x < w->width)
		{
			mlibx_draw_dot(w, x, y, 0xcc0000);
			x++;
		}
		y++;
	}
}

void	w_game_over(t_wind *w)
{
	w->w.player.health = 0;
	w->w.player.score = 0;
	w->w.player.gameover = 1;
	w_game_over_draw_bg(w);
}

int					w_game_timer_cycle(t_wind *w)
{
	clock_t			before;
	clock_t			diff;
	double			msec;
	int				trigger; // 10ms
	int				i;
	static double	millisec;

	before = clock();
	msec = 0;
	trigger = 10;
	i = 0;
	while (msec < trigger)
	{
		diff = clock() - before;
		msec = (double)diff * (double)1000 / (double)CLOCKS_PER_SEC;
		i++;
	}
	millisec += msec;
	//printf("timeout sec:%d, milliseconde: %d, i:%d\n", (int)millisec/1000, (int)millisec, i); // Print of time
	if (w->w.player.gameover == 0) // https://stackoverflow.com/questions/17167949/how-to-use-timer-in-c
		w->w.player.timeout = millisec/1000; // Set for wolf3d timeout
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img,
	w->img.x, w->img.y);
	if (w->w.player.timeout > TIMEOUT_GAME)
		w_game_over(w);
	put_info(w);
	return (0);
}
