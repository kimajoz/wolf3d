/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:05:51 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/06 23:14:40 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			print_map(t_wind *w)
{
	int			i;
	int			j;

	i = 0;
	//printf("nbr of line: %d\n", w->b.nbrtot_of_line);
	//printf("nbr elem on line: %d\n", w->b.nbr_elem_line[3]);
	while (i < (w->b.nbrtot_of_line * MMS))
	{
		j = 0;
		while (j < (w->b.nbr_elem_line[(i / MMS)] * MMS))
		{
			if (w->b.tab_int[i / MMS][j / MMS] > 0)
				mlibx_draw_pixel(w, j, i, "0xFFFFFF");
			j++;
		}
		i++;
	}
	if (mlibx_dot_in_window(w, w->cam.pos.x * MMS, w->cam.pos.z * MMS) == 1)
		mlibx_draw_pixel(w, w->cam.pos.x * MMS, w->cam.pos.z * MMS, "0xFF0000");
	w_print_radar_ray(w, w->cam.pos.x, w->cam.pos.z, w->cam.rot.y);
	w_print_radar_fov(w, w->cam.pos.x, w->cam.pos.z, w->cam.rot.y);
}

void			game_cycle(t_wind *w)
{
	print_map(w);
}

void			wolf3d(t_wind *w)
{
	move(w);
	w_cast_rays(w);
	print_map(w); //should init_map
	//game_cycle(w);
}
