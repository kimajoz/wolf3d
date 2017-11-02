/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:38:35 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/04 18:59:39 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				create_new_img(t_wind *w)
{
	ft_comment("create_new_img 01");
	printf("w->img.width : %d\n", w->img.width);
	printf("w->img.height : %d\n", w->img.height);
	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);
	ft_comment("create_new_img 01a");
	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bpp,
	&w->img.size_line, &w->img.endian);
	ft_comment("create_new_img 01b");
	w->img.octet_per_pixel = w->img.bpp / 8;
	ft_comment("create_new_img 04");
	wolf3d(w);
	ft_comment("create_new_img 05");
	return (0);
}
