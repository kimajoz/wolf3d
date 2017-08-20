/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:05:51 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/06 23:14:40 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
//#include <errno.h>
//#include <string.h>
//#include <stdio.h>
#include <time.h>
/*
void			update_minimap(t_wind *w)
{
	if (mlibx_dot_in_window(w, w->cam.pos.x * MMS, w->cam.pos.z * MMS) == 1)
		mlibx_draw_pixel(w, w->cam.pos.x * MMS, w->cam.pos.z * MMS, "0xFF0000");
	w_print_radar_ray(w, w->cam.pos.x, w->cam.pos.z, w->cam.rot.y);
	w_print_radar_fov(w, w->cam.pos.x, w->cam.pos.z, w->cam.rot.y);
}*/

void			init_minimap(t_wind *w)
{
	int			i;
	int			j;

	i = 0;
	//printf("nbr of line: %d\n", w->b.nbrtot_of_line);
	//printf("nbr elem on line: %d\n", w->b.nbr_elem_line[3]);
	while (i < (w->b.nbrtot_of_line * MMS))
	{
		j = 0;
		while (j < (w->b.nbr_elem_line[(i / MMS)] * MMS))
		{
			if (w->w.tab_int_spr[i / MMS][j / MMS] == 1) // Tables
				mlibx_draw_pixel(w, j, i, "0xFF0000");
			else if (w->w.tab_int_spr[i / MMS][j / MMS] == 4) //Lamps
				mlibx_draw_pixel(w, j, i, "0x00FF00");
			else if (w->b.tab_int[i / MMS][j / MMS] > 0)
				mlibx_draw_pixel(w, j, i, "0xFFFFFF");
			j++;
		}
		i++;
	}
	if (mlibx_dot_in_window(w, w->cam.pos.x * MMS, w->cam.pos.z * MMS) == 1)
		mlibx_draw_pixel(w, w->cam.pos.x * MMS, w->cam.pos.z * MMS, "0xFF0000");
	w_print_radar_ray(w, w->cam.pos.x, w->cam.pos.z, w->cam.rot.y);
	w_print_radar_fov(w, w->cam.pos.x, w->cam.pos.z, w->cam.rot.y);
	//update_minimap(w);
}

void			render_cycle(t_wind *w)
{
	init_minimap(w);
	//update_minimap(w);
	w_cast_rays(w);
}

void			game_cycle(t_wind *w)
{
	struct timespec		abs_time;
	struct timespec		time_delay;

	memset(&w->w.o.max_wait, 0, sizeof(w->w.o.max_wait));
	clock_gettime(CLOCK_REALTIME, &abs_time);
	// We calculate time since last game logic
	time_delay.tv_nsec = abs_time.tv_nsec - w->w.o.lastgamecycle_time.tv_nsec;
	printf("time_delay: %ld\n", time_delay.tv_nsec);
	move(w, time_delay);

	//max_wait.tv_sec = 2; /* wait at most 2 seconds */
	w->w.o.max_wait.tv_nsec = w->w.o.gamecycle_delay.tv_nsec; /* wait at most 30 milliseconde = 30 000 000 de nanoseconds */ //(30 / 1000)

	// Time we lost since last cycle
	if (time_delay.tv_nsec > w->w.o.max_wait.tv_nsec)
		w->w.o.max_wait.tv_sec = ft_fmax(1, w->w.o.max_wait.tv_nsec - (time_delay.tv_nsec - w->w.o.max_wait.tv_nsec));
	printf("max_wait: %ld\n", w->w.o.max_wait.tv_nsec);
	w->w.o.lastgamecycle_time.tv_nsec = abs_time.tv_nsec;
	//printf("lastgamecycle_time: %ld\n", w->w.o.lastgamecycle_time.tv_nsec);
	//ft_pthread_do_or_timeout(&max_wait, (void *)&data);
	//ft_set_time_out(w, wolf3d, cycle_delay);

	// pour continuer l'action de game_cycle() et continuer dans le même temps le cours du programme. On aura besoin de pthread, voir ici:
	// https://stackoverflow.com/questions/7738546/how-to-set-a-timeout-for-a-function-in-c
	// http://franckh.developpez.com/tutoriels/posix/pthreads/
}

void					init_pthread(t_wind *w)
{
	t_pthread			data;

	data.w = w;
	data.func = game_cycle; //data->func(data->w);
	data.reinit = init_pthread; //data->func(data->w);
	ft_putendl("generate new thread");
	ft_pthread_do_or_timeout(&w->w.o.max_wait, (void *)&data);
}

void					wolf3d(t_wind *w)
{
	//init_minimap(w);

		//ref here:
	// http://forums.devshed.com/programming-42/declaring-function-structure-545529.html
	//data.t = 55;
	//ft_set_time_out(w, game_cycle, cycle_delay);
	//game_cycle(w);
	//move(w);
	render_cycle(w);
	//init_minimap(w);

	//w_cast_rays(w);
	//w_render_sprites(w);
}
