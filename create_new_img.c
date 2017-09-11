/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:38:35 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/11 14:49:01 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				create_new_img(t_wind *w)
{
	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);

	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bpp,
	&w->img.size_line, &w->img.endian);
	//printf("endian screen: %d\n", w->img.endian);
	w->img.octet_per_pixel = w->img.bpp / 8;
	if (w->w.info.bg)
		w_draw_background_color(w);
	//mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_imgbg, w->img.x, w->img.y);
	//render_cycle(w);
	wolf3d(w);
	//render_screen(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	//mlx_put_image_to_window(w->mlx, w->win, w->w.text[0].ptr_img, w->img.x, w->img.y);
	//w_texture_walls(w);
	return (0);
}
