/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:25:35 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 21:14:11 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define BUTTONRELEASE		5
#define BUTTONRELEASEMASK	(1L<<3)
#define MOTIONNOTIFY		6
#define BUTTONMOTIONMASK	(1L<<13)
#define KEYPRESS			2
#define KEYPRESSMASK		(1L<<0)
#define KEYRELEASE			3
#define KEYRELEASEMASK		(1L<<1)

static void		set_parameters2(t_wind *w)
{
	w->w.info.raynumb = RAYNUMB;
	w->w.info.ray_minimap = 1;
	w->w.info.bg = 1;
	w->w.info.texture = 1;
	w->w.info.sound = 0;
	w_init_player_game(w);
	w->w.tmpgun = 0;
	w->w.player.ammunition = 7;
	w->w.info.tabinfo = 1;
	w->w.xtextp = 0;
	w->w.hit = (t_dpoint){0, 0, 0};
	w->w.hit2 = (t_dpoint){0, 0, 0};
	w->w.isprite = 0;
	w->w.player.timeout = 1 / 1000;
	w->w.player.prevtimeoutimg = 1 / 1000;
	w->w.player.prevtimeoutm = 1 / 1000;
	tab_info(w);
}

static void		set_parameters(t_wind *w)
{
	w->img.width = 800;
	w->img.height = 600;
	w->p.help = 1;
	w->p.m.button1 = 0;
	w->p.m.button2 = 0;
	w->p.m.button3 = 0;
	w->img.x = 0;
	w->img.y = 0;
	w->cam.vp.w = 600;
	w->cam.vp.h = 400;
	w->cam.pos.y = CUBESIZE / 2;
	w_init_player_pos(w);
	w->w.player.dir = 0;
	w->w.player.speed = 0;
	w->w.player.rotspeed = 5;
	w->w.player.movespeed = MOVESP;
	w->w.player.fov = FOV;
	w->w.marginwfset = w->b.nbr_elem_line[0] * MMS;
	w->w.marginw = w->w.marginwfset;
	w->w.color_mray = 0xFF0000;
	w->w.color_mfov = 0xFFFFFF;
	set_parameters2(w);
}

int				prog(char *filename)
{
	t_wind		w;

	pthread_mutex_init(&w.w.mutex_lock, NULL);
	w.w.bolpar = 0;
	w_init_player_pos(&w);
	if (!w_check_progstart(&w, filename))
		return (0);
	set_parameters(&w);
	init_texture(&w);
	init_guns(&w);
	w_init_screen(&w);
	create_new_img(&w);
	if (w.w.info.sound)
		w_play_music(&w, w.lpth.musicstart, S_STARTL1, 0);
	w_play_chronotime(&w);
	if (w.w.info.tabinfo)
		init_minimap(&w);
	mlx_hook(w.win, KEYPRESS, KEYPRESSMASK, keypress_function, &w);
	mlx_hook(w.win, KEYRELEASE, KEYRELEASEMASK, key_release_function, &w);
	mlx_loop_hook(w.mlx, hook_render, &w);
	mlx_expose_hook(w.win, expose_hook, &w);
	mlx_loop(w.mlx);
	return (0);
}

int				main(int argc, char **argv)
{
	if (argc != 2)
		ft_putendl("usage: ./wolf3d file.scn");
	else
		prog(argv[1]);
	return (0);
}
