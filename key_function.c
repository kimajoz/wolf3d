/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:01:12 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/27 19:21:41 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				is_blocking(t_dpoint pos, t_wind *w)
{
	if ((int)(w->b.tab_int[(int)pos.z][(int)pos.x]) > 0)
		return (1);
	return (0);
}

void			move(t_wind *w)
{
	t_dpoint	tmp;
	double		movestep;
	double		mult;

	tmp = (t_dpoint){0, 0, 0};
	// we calculate the mult of time_delay/gamecycle_delay
	//printf("gamecycle_delay: %d\n", (int)w->w.o.gamecycle_delay.tv_nsec);
	//printf("time_delay: %ld\n", time_delay.tv_nsec);
	//printf("time_delay minus: %d\n", (int)(w->w.o.gamecycle_delay.tv_nsec - time_delay.tv_nsec));
	//printf("time_delay minus2: %.3f\n", (double)(time_delay.tv_nsec / w->w.o.gamecycle_delay.tv_nsec));
	//printf("time_delay minus3: %.3f\n", (double)12000000 / 33000000);
	mult = 1;
	//mult = (int)(w->w.o.gamecycle_delay.tv_nsec - time_delay.tv_nsec) / (int)w->w.o.gamecycle_delay.tv_nsec;
	//mult = (double)(time_delay.tv_nsec) / w->w.o.gamecycle_delay.tv_nsec;
	//printf("move time_delay.tv_nsec : %ld\n", time_delay.tv_nsec);
	//printf("move gamecycle_delay.tv_nsec : %ldn", w->w.o.gamecycle_delay.tv_nsec);
	//printf("move mult: %.3f\n", mult);
	/*printf("time_delay2: %.3f\n", time_delay);
	printf("w->w.o.gamecycle_delay: %d\n", w->w.o.gamecycle_delay);
	printf("mult: %.3f\n", mult);*/

	movestep = mult * w->w.player.speed * w->w.player.movespeed;
	w->cam.rot.y = mult * ft_rot_fabs(w->cam.rot.y + w->w.player.dir * w->w.player.rotspeed);
	tmp.x = w->cam.pos.x + cos(ft_degreetorad(w->cam.rot.y)) * movestep;
	tmp.z = w->cam.pos.z + sin(ft_degreetorad(w->cam.rot.y)) * movestep;
	if (is_blocking(tmp, w) != 1 || w->w.tab_int_spr[(int)tmp.z][(int)tmp.x].block != 1)
	{
		w->cam.pos.x = tmp.x;
		w->cam.pos.z = tmp.z;
	}
	else
		ft_putendl("blocking");
}

static void		keypress_function01(int keycode, t_wind *w)
{
	if (keycode == U_ARROW || keycode == D_ARROW || keycode == R_ARROW || keycode == L_ARROW)
		w->w.player.kp.upwalk = 0;
	if (((keycode == U_ARROW) || (keycode == D_ARROW)) && w->w.info.sound)
	{
		ft_putendl("appuie");
		//pthread_cancel(w->lpth.fxwalk); // Annule l'ancien thread de son
		w_play_music(w, w->lpth.fxwalk, "sounds/loops/footsteps-4_loop.wav", 0);
	}
	if (keycode == L_ARROW)
		w->w.player.dir = -1;
	else if (keycode == R_ARROW)
		w->w.player.dir = 1;
	else if (keycode == U_ARROW)
		w->w.player.speed = 1;
	else if (keycode == D_ARROW)
		w->w.player.speed = -1;
	else if (keycode == SPACE)
	{
		ft_putendl("space");
		w->w.player.opendoor = 1;
	}
	else if (keycode == CTRL_R)
	{
		ft_putendl("fire");
		w->w.player.fire = 1;
	}
	else if (keycode == KEY_R)
	{
		w->w.player.ammunition += 7;
		if (w->w.info.sound)
		{
			pthread_cancel(w->lpth.fxguncocking); // Annule l'ancien thread de son
			w_play_music(w, w->lpth.fxguncocking, "sounds/loops/gun-cocking-01.wav", 0);
		}
	}
}

static void		keypress_function02(int keycode, t_wind *w)
{	if (keycode == KEY_1)
		w->w.info.raynumb = 60;
	else if (keycode == KEY_2)
	{
		w->w.info.raynumb = (w->w.info.raynumb < w->width) ?
			(w->w.info.raynumb - 10) : w->w.info.raynumb;
	}
	else if (keycode == KEY_3)
	{
		w->w.info.raynumb = (w->w.info.raynumb < w->width) ?
			(w->w.info.raynumb + 10) : w->w.info.raynumb;
	}
	else if (keycode == KEY_4)
		w->w.info.raynumb = 600;
	else if (keycode == KEY_5)
		w->w.info.ray_minimap = (w->w.info.ray_minimap) ? 0 : 1;
	else if (keycode == KEY_6)
		w->w.info.bg = (w->w.info.bg) ? 0 : 1;
	else if (keycode == KEY_7)
		w->w.info.texture = (w->w.info.texture) ? 0 : 1;
	else if (keycode == KEY_8)
		w->w.info.sound = (w->w.info.sound) ? 0 : 1;
	else if (keycode == TAB_L)
		w->w.info.tabinfo = (w->w.info.tabinfo) ? 0 : 1;
}

int				keypress_function(int keycode, t_wind *w)
{
	//ft_putnbr(keycode);
	//ft_putchar('\n');
	if (keycode == EXIT)
		exit(0);
	if (!w->w.player.gameover && !w->w.player.win)
	{
		//ft_putendl("press");
		keypress_function01(keycode, w);
		keypress_function02(keycode, w);
		mlx_destroy_image(w->mlx, w->img.ptr_img);
		create_new_img(w);
		//mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	}
	return (0);
}
