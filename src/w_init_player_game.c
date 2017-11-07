/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_init_player_game.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 18:48:27 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 20:50:30 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			w_init_player_pos(t_wind *w)
{
	w->cam.rot.x = 0;
	w->cam.rot.z = 0;
	w->cam.pos.x = 1.5;
	w->cam.pos.z = 1.5;
	w->cam.rot.y = 0;
}

void			w_init_player_game(t_wind *w)
{
	w->w.player.gameover = 0;
	w->w.player.win = 0;
	w->w.player.points = 0;
	w->w.player.kills = 0;
	w->w.player.totalscore = 0;
	w->w.player.health = 100;
	w->w.player.opendoor = 0;
	w->w.player.fire = 0;
	w->w.player.object = 0;
}

void			w_init_screen(t_wind *w)
{
	int			y;
	int			x;

	if (!(w->screen = malloc(w->height * sizeof(t_screen *))))
		exit(0);
	y = 0;
	while (y < w->height)
	{
		x = 0;
		if (!(w->screen[y] = malloc(w->width * sizeof(t_screen))))
			exit(0);
		while (x < w->width)
		{
			w->screen[y][x].color = 0;
			w->screen[y][x].zdepth = 1000;
			x++;
		}
		y++;
	}
}

void			w_clear_screen(t_wind *w)
{
	int			y;
	int			x;

	y = 0;
	while (y < w->height)
	{
		x = 0;
		while (x < w->width)
		{
			w->screen[y][x].color = 0;
			w->screen[y][x].zdepth = 1000;
			x++;
		}
		y++;
	}
}

void			w_render_screen(t_wind *w)
{
	int			y;
	int			x;

	y = 0;
	while (y < w->height)
	{
		x = 0;
		while (x < w->width)
		{
			mlibx_draw_dot(w, x, y, w->screen[y][x].color);
			x++;
		}
		y++;
	}
}
