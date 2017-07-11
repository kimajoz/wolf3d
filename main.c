/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:25:35 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/06 23:14:59 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define BUTTONRELEASE		5
#define BUTTONRELEASEMASK	(1L<<3)
#define MOTIONNOTIFY		6
#define BUTTONMOTIONMASK	(1L<<13)
#define KEYPRESS			2
#define KEYPRESSMASK		(1L<<0)
#define KEYRELEASE			3
#define KEYRELEASEMASK		(1L<<1)

static int		set_parameters(t_wind *w)
{
	w->img.width = 800;
	w->img.height = 600;
	w->img.margin = 100;
	w->p.help = 1;
	w->p.m.button1 = 0;
	w->p.m.button2 = 0;
	w->p.m.button3 = 0;
	w->img.x = 0;
	w->img.y = 0;
	w->cam.vp.w = 600;
	w->cam.vp.h = 400;
	w->cam.pos.y = CUBESIZE / 2;
	w->cam.pos.x = 1.5;
	w->cam.pos.z = 0.5;
	w->cam.rot.y = 0;
	w->w.color_mray = "0xFF0000";
	w->w.color_mfov = "0xFFFFFF";
	w->w.info.raynumb = RAYNUMB;
	w->w.info.ray_minimap = 0;
	w->w.info.bg = 0;
	w->w.info.texture = 0;
	w->w.info.sound = 0;
	return (0);
}

int				prog(char *filename)
{
	t_wind		w;

	w.width = 800;
	w.height = 600;
	w = create_new_window("Wolf3d", w.width, w.height);
	if (rt_file(filename, w.b.y, &w) == NULL)
		return (0);
	else
		w.b.tab_int = rt_file(filename, w.b.y, &w);
	set_parameters(&w);
	create_new_img(&w);
	mlx_hook(w.win, KEYPRESS, KEYPRESSMASK, keypress_function, &w);
	mlx_hook(w.win, KEYRELEASE, KEYRELEASEMASK, key_release_function, &w);
	mlx_expose_hook(w.win, expose_hook, &w);
	mlx_loop(w.mlx);
	return (0);
}

int				main(int argc, char **argv)
{
	if (argc != 2)
		ft_putstr("usage");
	else
		prog(argv[1]);
	return (0);
}
