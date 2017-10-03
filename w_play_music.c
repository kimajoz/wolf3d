/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_play_music.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:25:30 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/27 19:16:14 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <pthread.h>
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

// For sound wav references
// http://soundbible.com/tags-walking.html
// To cut wav file: https://ubuntuforums.org/showthread.php?t=1719664

void			*w_play(void *data)
{
	t_wind		*w;

	ft_putendl("w_play");
	w = (t_wind *)data;
	//printf("playtheme: %.3f", w->w.dist);
	//w->w.player.timemusic = (int)ft_get_sound_duration(w->w.songname, OS);
	if (ft_strstr(w->w.songname, "walk"))
		w->w.timemusic = 1;
	if (ft_strstr(w->w.songname, "Heartbeat"))
		w->w.timemusic = 1;
	if (ft_strstr(w->w.songname, "gunshot") || ft_strcmp(w->w.songname, "bullet"))
		w->w.timemusic = 1;
	//printf("sound duration: %.3f\n", w->w.timemusic);
	if ((w->w.player.prevtimeoutm + w->w.timemusic) < w->w.player.timeout || !w->w.player.prevtimeoutm
		|| ft_strstr(w->w.songname, "gunshot") // exception for unlimited repetead fireshoot
		|| ft_strstr(w->w.songname, "gun-cocking")) // exception for gun reload
	{
		//ft_putstr("-> Ok to play ");
		//ft_putendl(w->w.songname);
		w->w.player.prevtimeoutm = w->w.player.timeout;
		ft_play_sound(w->w.songname, OS);
	}
	else
	{
		//ft_putstr("-> Not Ok to play ");
		//printf("prevtimeoutm+music: %.3f < timeout: %.3f\n", (w->w.player.prevtimeoutm + w->w.timemusic), w->w.player.timeout);
		//ft_putstr(" ou");
		//ft_putnbr(w->w.player.prevtimeoutm);
		//ft_putendl(" n'existe pas");
	}
	return (0);
}

void			*w_play_loop(void *data)
{
	t_wind		*w;

	//ft_putendl("w_play_loop");
	//https://stackoverflow.com/questions/30883238/running-background-process-in-c-using-pthread
	w = (t_wind *)data;
	//ft_putendl("play music");
	//ft_putendl("start loop");
	//printf("playtheme: %.3f", w->w.dist);
	//ft_play_sound("sounds/loops/footsteps-4.wav");
	while (1)
		ft_play_sound(w->w.songname, OS);
	return (0);
}

int				w_play_music(t_wind *w, pthread_t addresspth, char *url, int loop)
{

	w->w.songname = ft_strnew(ft_strlen(url));
	ft_strcpy(w->w.songname, url);
	//printf("playtheme3: %s\n", w->w.songname);
	if (loop)
		pthread_create( &addresspth, NULL, w_play_loop, (void*)w);
	else
		pthread_create( &addresspth, NULL, w_play, (void*)w);
	pthread_join(w->lpth.musicstart, NULL); // Pour que le script se termine avant la fin du programme
	//pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); // autorise l'annulation du thread
	//pthread_setcanceltype(3, PTHREAD_CANCEL_DEFERRED); // Asynchronous cancelability means that the thread can be canceled at any time -> numb 3
	return (0);
}
