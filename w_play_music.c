/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_play_music.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:25:30 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 16:31:36 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			*w_play(void *data)
{
	t_wind		*w;

	w = (t_wind *)data;
	if (ft_strstr(w->w.songname, "footsteps") || ft_strstr(w->w.songname,
			"Heartbeat"))
		w->w.timemusic = 2;
	if (ft_strstr(w->w.songname, "gunshot") || ft_strcmp(w->w.songname,
			"bullet"))
		w->w.timemusic = 0.5;
	if ((w->w.player.prevtimeoutm + w->w.timemusic) < w->w.player.timeout ||
			!w->w.player.prevtimeoutm)
	{
		w->w.player.prevtimeoutm = w->w.player.timeout;
		ft_play_sound(w->w.songname, OS);
		if (!w->w.songname)
			free(w->w.songname);
	}
	return (0);
}

void			*w_play_loop(void *data)
{
	t_wind		*w;

	w = (t_wind *)data;
	while (1)
		ft_play_sound(w->w.songname, OS);
	return (0);
}

int				w_play_music(t_wind *w, pthread_t addresspth, char *url,
		int loop)
{
	pthread_mutex_lock(&w->w.mutex_lock);
	w->w.songname = url;
	if (loop)
		pthread_create(&addresspth, NULL, w_play_loop, (void*)w);
	else
		pthread_create(&addresspth, NULL, w_play, (void*)w);
	pthread_mutex_unlock(&w->w.mutex_lock);
	return (0);
}

void			w_sound_toggle(t_wind *w)
{
	if (w->w.info.sound)
	{
		w->w.info.sound = 0;
		w_play_music(w, w->lpth.fxwalk, S_ONSOUND, 0);
	}
	else
	{
		w->w.info.sound = 1;
		w_play_music(w, w->lpth.fxturnonsound, S_OFFSOUND, 0);
	}
}
