/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_game_over.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 17:58:01 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 16:31:04 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		w_win_level(t_wind *w)
{
	static	int	i;

	w_draw_colored_bg(w, 0x0000cc);
	if (!i && w->w.info.sound)
	{
		w_play_music(w, w->lpth.musicgamewin, S_GAMEOVER, 0);
		pthread_join(w->lpth.musicgamewin, NULL);
		i = 1;
	}
}

void		check_win_game(t_wind *w)
{
	if (w->w.bolpar == 1)
	{
		if (((int)w->cam.pos.x == w->w.player.end_pos[0]) &&
		((int)w->cam.pos.z == w->w.player.end_pos[1]) && !w->w.player.win)
			w->w.player.win = 1;
	}
}

void		w_game_over(t_wind *w)
{
	w->w.player.health = 0;
	w->w.player.totalscore = 0;
	w->w.player.gameover = 1;
	w_draw_colored_bg(w, 0xcc0000);
	if (w->w.info.sound)
	{
		w_play_music(w, w->lpth.musicgameover, S_GAMEOVER, 0);
		pthread_join(w->lpth.musicgameover, NULL);
	}
}
