/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_draw_background_color.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 19:47:24 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/06 21:48:13 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			w_draw_background_color(t_wind *w)
{
	int			i;
	t_point		p;
	t_point		pd;

	i = 0;
	while (i < w->height)
	{
		p = (t_point){0, i, 0};
		pd = (t_point){w->width, i, 0};
		if (i < w->height / 2)
			mlibx_draw_pixel_line(p, pd, w, "0xbdbdbd");
		else
			mlibx_draw_pixel_line(p, pd, w, "0x939393");
		i++;
	}
}
