/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_game_timer_cycle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 20:19:22 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/12 20:39:20 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

void	w_game_over(t_wind *w)
{
	w->w.player.health = 0;
	w->w.player.score = 0;
	w->w.player.gameover = 1;
}

int		w_game_timer_cycle(t_wind *w)
{
	clock_t				before;
	clock_t				diff;
	double				msec;
	int					trigger; // 10ms
	int					i;
	static double		millisec;
	//static int			sec;

	// https://stackoverflow.com/questions/17167949/how-to-use-timer-in-c
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
	w->w.player.timeout = millisec/1000; // Set for wolf3d timeout
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img,
	w->img.x, w->img.y);
	put_info(w);
	if (w->w.player.timeout > TIMEOUT_GAME)
		w_game_over(w);
	return (0);
}
