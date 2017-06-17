/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 14:52:45 by pbillett          #+#    #+#             */
/*   Updated: 2017/05/10 19:09:29 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define LEFTM 4
#define ROW 20
#define BL 6

static void			put_string(char *s, int l, int c, t_wind *w)
{
	mlx_string_put(w->mlx, w->win, 3 + c * 10, l * 20, 0xFFFFFF, s);
}

void				put_info_cam(t_wind *w, int leftm, int row, int bl)
{
	put_string("Camera :", row, 1, w);
	row = 21;
	put_string("pos.x:", row, leftm, w);
	put_string(ft_itoa((int)w->cam.pos.x), row, leftm + bl, w);
	put_string("y: ", row, leftm + bl + 4, w);
	put_string(ft_itoa((int)w->cam.pos.y), row, leftm + bl + 6, w);
	put_string("z: ", row, leftm + bl + 10, w);
	put_string(ft_itoa((int)w->cam.pos.z), row, leftm + bl + 12, w);
	row = 22;
	put_string("rot.x:", row, leftm, w);
	put_string(ft_itoa((int)w->cam.rot.x), row, leftm + bl, w);
	put_string("y: ", row, leftm + bl + 4, w);
	put_string(ft_itoa((int)w->cam.rot.y), row, leftm + bl + 6, w);
	put_string("z: ", row, leftm + bl + 10, w);
	put_string(ft_itoa((int)w->cam.rot.z), row, leftm + bl + 12, w);
}
/*
void				put_info_light(t_wind *w, int leftm, int row, int bl)
{
	row = 23;
	put_string("Light :", row, 1, w);
	put_string(w->rt.lst_lightsel->data->name, row, bl + 4, w);
	row = 24;
	put_string("pos x: ", row, leftm, w);
	put_string(ft_itoa((int)w->rt.lst_lightsel->data->pos.x), row, leftm + bl, w);
	put_string("y: ", row, leftm + bl + 4, w);
	put_string(ft_itoa((int)w->rt.lst_lightsel->data->pos.y), row, leftm + bl + 6, w);
	put_string("z: ", row, leftm + bl + 10, w);
	put_string(ft_itoa((int)w->rt.lst_lightsel->data->pos.z), row, leftm + bl + 12, w);
	row = 25;
	put_string("rot x: ", row, leftm, w);
	put_string(ft_itoa((int)w->rt.lst_lightsel->data->rot.x), row, leftm + bl, w);
	put_string("y: ", row, leftm + bl + 4, w);
	put_string(ft_itoa((int)w->rt.lst_lightsel->data->rot.y), row, leftm + bl + 6, w);
	put_string("z: ", row, leftm + bl + 10, w);
	put_string(ft_itoa((int)w->rt.lst_lightsel->data->rot.z), row, leftm + bl + 12, w);
}

void				put_info_sel(t_wind *w)
{
	int				row;
	int				leftm;
	int				bl;

	leftm = 4;
	row = 20;
	bl = 6;
	put_info_cam(w, leftm, row, bl);
	put_info_light(w, leftm, row, bl);
	row = 26;
	put_string("Object :", row, 1, w);
	put_string(w->rt.lst_objsel->data->name, row, bl + 4, w);
	row = 27;
	put_string("pos x: ", row, leftm, w);
	put_string(ft_itoa((int)w->rt.lst_objsel->data->pos.x), row, leftm + bl, w);
	put_string("y: ", row, leftm + bl + 4, w);
	put_string(ft_itoa((int)w->rt.lst_objsel->data->pos.y), row, leftm + bl + 6, w);
	put_string("z: ", row, leftm + bl + 10, w);
	put_string(ft_itoa((int)w->rt.lst_objsel->data->pos.z), row, leftm + bl + 12, w);
	row = 28;
	put_string("rot x: ", row, leftm, w);
	put_string(ft_itoa((int)w->rt.lst_objsel->data->rot.x), row, leftm + bl, w);
	put_string("y: ", row,  leftm + bl + 4, w);
	put_string(ft_itoa((int)w->rt.lst_objsel->data->rot.y), row, leftm + bl + 6, w);
	put_string("z: ", row,  leftm + bl + 10, w);
	put_string(ft_itoa((int)w->rt.lst_objsel->data->rot.z), row, leftm + bl + 12, w);
	row = 29;
	//put_string("ui_sel:", row, 1, w);
	//put_string(ft_itoa((int)(w->rt.ui_sel)), row, 7, w);
}*/

void				put_info(t_wind *w)
{
	int				row;

	/*row = 1;
	put_string(">", w->rt.ui_sel, 0, w);
	put_string("Sel elem: !/:", row, 1, w);
	put_string("speed:", row, 70, w);
	put_string(ft_itoa((int)w->rt.speed_rt), row, 78, w);
	row = 2;
	put_string("Sel in elem: Zoom +/-", row, 1, w);
	row = 3;
	put_string("Move: Arrows (+Pgup/Pgdown)", row, 1, w);
	row = 4;
	put_string("Rotate: Numpad Arrows (+1/3)", row, 1, w);*/
	row = 5;
	//put_string("Render Speed : num 1, 2 (not numpad)", row, 1, w);
	//put_info_sel(w);
	put_info_cam(w, LEFTM, row, BL);
}
