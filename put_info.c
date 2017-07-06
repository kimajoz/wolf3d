/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 14:52:45 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/06 22:55:20 by pbillett         ###   ########.fr       */
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
	row = 15;
	put_string("pos.x:", row, leftm, w);
	put_string(ft_itoa((int)w->cam.pos.x), row, leftm + bl, w);
	put_string("y: ", row, leftm + bl + 4, w);
	put_string(ft_itoa((int)w->cam.pos.y), row, leftm + bl + 6, w);
	put_string("z: ", row, leftm + bl + 10, w);
	put_string(ft_itoa((int)w->cam.pos.z), row, leftm + bl + 12, w);
	row = 16;
	put_string("rot.x:", row, leftm, w);
	put_string(ft_itoa((int)w->cam.rot.x), row, leftm + bl, w);
	put_string("y: ", row, leftm + bl + 4, w);
	put_string(ft_itoa((int)w->cam.rot.y), row, leftm + bl + 6, w);
	put_string("z: ", row, leftm + bl + 10, w);
	put_string(ft_itoa((int)w->cam.rot.z), row, leftm + bl + 12, w);
}

void				put_info(t_wind *w)
{
	int				row;
	int				column;

	column = 17;
	row = 14;
	put_info_cam(w, LEFTM, row, BL);
	row = 20;
	put_string("Number of rays: ", row, 1, w);
	put_string(ft_itoa((int)w->w.info.raynumb), row, column, w);
	row = 22;
	put_string("Minimap rays: ", row, 1, w);
	put_string(ft_itoa((int)w->w.info.ray_minimap), row, column, w);
	row = 23;
	put_string("Background: ", row, 1, w);
	put_string(ft_itoa((int)w->w.info.bg), row, column, w);
	row = 24;
	put_string("Textures: ", row, 1, w);
	put_string(ft_itoa((int)w->w.info.texture), row, column, w);
	row = 25;
	put_string("Sound: ", row, 1, w);
	put_string(ft_itoa((int)w->w.info.sound), row, column, w);
}
