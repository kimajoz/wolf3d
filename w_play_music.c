/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_play_music.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:25:30 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/14 20:41:05 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
void			w_play_set_sounds_url(t_wind *w)
{
	int			nbmusic;
	int			i;

	nbmusic = 12;
	w->w.music.urls = malloc(sizeof(char *) * nbmusic);
	i = 0;
	while (i < nbmusic)
	{
		ft_strnew();
		i++;
	}
}*/

void			*w_play_m_theme(void *data)
{
	t_wind		*w;

	w = (t_wind *)data;
	//ft_putendl("play music");
	printf("playtheme: %.3f", w->w.dist);
	//ft_play_sound("sounds/loops/footsteps-4.wav");
	while (1)
		ft_play_sound("sounds/loops/M-Audio-Venom-Mysterio-C2.wav", OS);
	return (0);
}

/*int						w_pthread_music(t_wind *w)
{
	struct timespec		max_wait;
	t_pthread			*data;

	memset(&max_wait, 0, sizeof(max_wait));*/
	
	/* wait at most 2 seconds */
	//max_wait.tv_sec = 20;
	//max_wait.tv_sec = 2;
	/* wait at most 30 milliseconde = 30 000 000 de nanoseconds */
	//max_wait.tv_nsec = 30000000;
	//ref here:
	// http://forums.devshed.com/programming-42/declaring-function-structure-545529.html
	/*data = malloc(sizeof(t_pthread *));
	data->t = 55;
	data->w = w;
	data->func = (void *)(*w_play_m_theme)(w);*/
	//data->func = (void)(*w_play_m_theme)(w);
	//data->func(data->w);
	//ft_pthread_do_or_timeout(&max_wait, (void *)data);
	//ft_set_time_out(w, game_cycle, cycle_delay);
	//return (0);
//}

int				w_play_music(t_wind *w)
{
	//int th1;

	printf("playtheme: %.3f", w->w.dist);
	// create the thread
	pthread_create( &w->lpth.ptmusic, NULL, w_play_m_theme, (void*)w);
	//w_pthread_music(w);
	return (0);
}
