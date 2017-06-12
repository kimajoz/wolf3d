/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:17:23 by pbillett          #+#    #+#             */
/*   Updated: 2017/05/24 12:50:07 by pbillett         ###   ########.fr       */
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
	return (0);
}

int				wolf3d(char *filename)
{
	t_wind		w;
	double		cubesize;
	double		pheight;
	double		fov;
	double		vp;
	double		vpc;
	double		distptovp;
	double		anglebetrays;

	cubesize = 64;
	pheight = cubesize / 2;
	vp.w = 320;
	vp.h = 200;
	vpc.w = vp.w / 2;
	vpc.h = vp.h / 2;
	distptovp = vpc.w / tan(fov/2);
	anglebetrays = fov / vp.w;

	w.width = 800;
	w.height = 600;
	w = create_new_window("Wolf3d", w.width, w.height);
	// Initialise parameters of rt:
	w.rt.e.pos.x = 0;
	w.rt.e.pos.y = 0;
	w.rt.e.pos.z = 50;

	if (rt_file(filename, w.b.y, &w) == NULL)
		return (0);
	else
		w.b.tab_int = rt_file(filename, w.b.y, &w);
	//w.b.filename = (char *)malloc((ft_strlen(filename) + 1) * sizeof(char));
	//w.b.filename = ft_strcpy(w.b.filename, filename);
	set_parameters(&w);
	create_new_img(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.ptr_img, w.img.x, w.img.y);
	//mlx_mouse_hook(w.win, mousepress_function, &w);
	//mlx_hook(w.win, BUTTONRELEASE, BUTTONRELEASEMASK, mouse_release_function,
	//&w);
	//mlx_hook(w.win, MOTIONNOTIFY, BUTTONMOTIONMASK, mouse_motion_function, &w);
	mlx_hook(w.win, KEYPRESS, KEYPRESSMASK, keypress_function, &w);
	mlx_hook(w.win, KEYRELEASE, KEYRELEASEMASK, key_release_function, &w);
	//mlx_loop_hook(w.mlx, turntable, &w);
	mlx_expose_hook(w.win, expose_hook, &w);
	mlx_loop(w.mlx);
	return (0);
}
