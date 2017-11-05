/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlibx_draw_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:34:12 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 16:34:15 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void			mlibx_draw_pixel(t_wind *w, int x, int y, char *hexacolor)
{
	t_rgbcolor	rgbcolor;

	rgbcolor = ft_hexatorgb(hexacolor);
	*(w->img.pxl_ptr + (y * w->img.size_line) +
	(x * w->img.octet_per_pixel)) = rgbcolor.r;
	*(w->img.pxl_ptr + (y * w->img.size_line) +
	(x * w->img.octet_per_pixel) + 1) = rgbcolor.g;
	*(w->img.pxl_ptr + (y * w->img.size_line) +
	(x * w->img.octet_per_pixel) + 2) = rgbcolor.b;
}
