/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:05:51 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/27 20:49:55 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
//#include <errno.h>
//#include <string.h>
//#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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
			if (w->w.tab_int_spr[i / MMS][j / MMS].num == 1) // Tables
				mlibx_draw_pixel(w, j, i, "0xFF0000");
			else if (w->w.tab_int_spr[i / MMS][j / MMS].num == 4) //Lamps
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
/*
void			render_cycle(t_wind *w)
{
	init_minimap(w);
	//update_minimap(w);
	w_cast_rays(w);
}*/
void			tab_info(t_wind *w)
{
	if (!w->w.info.tabinfo)
	{
		w->w.marginw = 0;
		w->w.info.raynumb = w->width;
		w->w.player.fov = 70;
		if (w->w.info.bg)
			w_draw_background_color(w);
	}
	else
	{
		w->w.marginw = w->b.nbr_elem_line[0] * MMS;
		w->w.info.raynumb = w->width - w->w.marginw;
		w->w.player.fov = 50;
	}
}

int						game_cycle(t_wind *w)
{
	//struct timespec		now;
	//struct timespec		time_delay;
	//struct timespec		cycle_delay;

	//clock_gettime(CLOCK_REALTIME, &now);
	// We calculate time since last game logic
	//time_delay.tv_sec = now.tv_sec - w->w.o.lastgamecycle_time.tv_sec;
	//time_delay.tv_nsec = now.tv_nsec - w->w.o.lastgamecycle_time.tv_nsec;
	//printf("time_delay: %ld sec %ld nsec\n", time_delay.tv_sec, time_delay.tv_nsec);

	//move(w, time_delay);
	move(w);
	//cycle_delay.tv_nsec = w->w.o.gamecycle_delay.tv_nsec;

	//printf("time_delay: %.3f\n", time_delay);
	/*if (time_delay.tv_nsec < cycle_delay.tv_nsec)
	{
		nanosleep(&cycle_delay, NULL);
		printf("time_delay smaller\n");
	}*/
	// Time we lost since last cycle
	//if (time_delay > cycle_delay)
		//cycle_delay = ft_fmax(1, cycle_delay - (time_delay - cycle_delay));
	//w->w.o.lastgamecycle_time = now;

	//ft_set_time_out(w, wolf3d, cycle_delay);

	// pour continuer l'action de game_cycle() et continuer dans le même temps le cours du programme. On aura besoin de pthread, voir ici:
	// https://stackoverflow.com/questions/7738546/how-to-set-a-timeout-for-a-function-in-c
	// http://franckh.developpez.com/tutoriels/posix/pthreads/
	return (0);
}

void					wolf3d(t_wind *w)
{
	tab_info(w);
	//ft_putendl("start render");
	//init_minimap(w);
	w_clear_vis_sprites(w);
	game_cycle(w);
	//move(w);
	//render_cycle(w);

	//init_minimap(w);
	// https://dev.opera.com/articles/3d-games-with-canvas-and-raycasting-part-2/
	w_cast_rays(w);
	w_gun_fire(w);
	//ft_putendl("end render");
	//w_render_sprites(w);
}
