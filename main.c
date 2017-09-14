/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:25:35 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/14 21:01:28 by pbillett         ###   ########.fr       */
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

static void		init_player_pos(t_wind *w)
{
	w->cam.rot.x = 0;
	w->cam.rot.z = 0;
	if (w->w.player.init_pos != NULL)
	{
		w->cam.pos.x = w->w.player.init_pos[0] + 0.5;
		w->cam.pos.z = w->w.player.init_pos[1] + 0.5;
		w->cam.rot.y = w->w.player.init_pos[2];
	}
	else
	{ // Default values (if not map.par files)
		w->cam.pos.x = 1.5;
		w->cam.pos.z = 1.5;
		w->cam.rot.y = 0;
	}
}

static void		init_player_game(t_wind *w)
{
	w->w.player.gameover = 0;
	w->w.player.score = 0;
	w->w.player.health = 100;
	w->w.player.object = ft_strnew(ft_strlen("No objects"));
	ft_strcpy(w->w.player.object, "No objects");
}

static void		init_screen(t_wind *w)
{
	int			y;
	int			x;

	w->screen = malloc(w->height * sizeof(t_screen *));
	y = 0;
	while (y < w->height)
	{
		x = 0;
		w->screen[y] = malloc(w->width * sizeof(t_screen));
		while (x < w->width)
		{
			w->screen[y][x].color = 0;
			w->screen[y][x].zdepth = 0;
			x++;
		}
		y++;
	}
}

static void		clear_screen(t_wind *w)
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
			w->screen[y][x].zdepth = 0;
			x++;
		}
		y++;
	}
}

void			render_screen(t_wind *w)
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
	clear_screen(w);
}

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
	init_player_pos(w);
	w->w.player.rotspeed = 5;
	w->w.player.movespeed = MOVESP;
	w->w.marginw = w->b.nbr_elem_line[0] * MMS;
	w->w.color_mray = "0xFF0000";
	w->w.color_mfov = "0xFFFFFF";
	w->w.info.raynumb = RAYNUMB;
	w->w.info.ray_minimap = 1;
	w->w.info.bg = 1;
	w->w.info.texture = 1;
	w->w.info.sound = 0;
	init_player_game(w);
	w->w.o.lastgamecycle_time.tv_sec = 0;
	w->w.o.lastgamecycle_time.tv_nsec = 0;
	//w->w.o.lastgamecycle_time = 0;
	//w->w.o.gamecycle_delay = 1000 / 30; //30fps
	w->w.o.gamecycle_delay.tv_sec = 0; //30fps
	//w->w.o.gamecycle_delay.tv_nsec = 100000000; //30fps
	w->w.o.gamecycle_delay.tv_nsec = 330000000; //30fps
	return (0);
}

char			*new_file_name(char *oldfilename, char* ext)
{
	char		*str;
	int			len;

	len = ft_strlen(ext);
	str = ft_strnew(ft_strlen(oldfilename));
	ft_strcpy(str, ft_strsub(oldfilename, 0, ft_strlen(oldfilename) - len));
	ft_strcat(str, ext);
	return (str);
}

int				prog(char *filename)
{
	t_wind		w;
	char		*fsprites;
	char		*fparam;

	w.width = 800;
	w.height = 600;
	if (!ft_strstr(filename, "scn"))
	{
		ft_putendl("File wrong type: Needed .scn input file extension.");
		return (0);
	}
	w = create_new_window("Wolf3d", w.width, w.height);
	if (!rt_file(filename, w.b.y, &w, 1))
		return (0);
	else
		rt_file(filename, w.b.y, &w, 1);
	// Load sprites and params if any
	fsprites = new_file_name(filename, ".spr");
	fparam = new_file_name(filename, ".par");
	rt_file(fsprites, w.b.y, &w, 0);
	if (!rt_file(fparam, w.b.y, &w, 1))
		return (0);
	set_parameters(&w);
	init_texture(&w);
	init_screen(&w);
	create_new_img(&w);
	//wolf3d(&w);
	//init_pthread(&w);
	//mlx_put_image_to_window(w.mlx, w.win, w.img.ptr_img, w.img.x, w.img.y);
	//game_cycle(w);
	//render_cycle(w);
	init_minimap(&w); //init minimap
	mlx_hook(w.win, KEYPRESS, KEYPRESSMASK, keypress_function, &w);
	mlx_hook(w.win, KEYRELEASE, KEYRELEASEMASK, key_release_function, &w);
	mlx_loop_hook(w.mlx, w_game_timer_cycle, &w);
	//mlx_loop_hook(w.mlx, game_cycle, &w);
	mlx_expose_hook(w.win, expose_hook, &w);
	mlx_loop(w.mlx);
	return (0);
}

int				main(int argc, char **argv)
{
	w_play_music();
	if (argc != 2)
		ft_putstr("usage");
	else
		prog(argv[1]);
	return (0);
}
