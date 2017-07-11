/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:38:35 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/06 22:31:41 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				create_new_img(t_wind *w)
{
	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);

	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel,
	&w->img.size_line, &w->img.endian_type);
	w->img.octet_per_pixel = w->img.bits_per_pixel / 8;
	if (w->w.info.bg)
		w_draw_background_color(w);
	//mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_imgbg, w->img.x, w->img.y);
	wolf3d(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	//w_texture_walls(w);
	return (0);
}
