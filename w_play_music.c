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
	ft_play_sound(w->w.songname, OS);
	return (0);
}

void			*w_play_loop(void *data)
{
	t_wind		*w;

	ft_putendl("w_play_loop");
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
	return (0);
}
