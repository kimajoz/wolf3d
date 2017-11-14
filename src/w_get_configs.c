/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_get_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:28:14 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/14 18:38:15 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int				getcolor(t_img *img, int x, int y)
{
	int			color;
	int			c;

	c = y * img->size_line + (x * (img->bpp / 8));
	color = img->pxl_ptr[c];
	if (color == -120 && img->pxl_ptr[c + 1] == 0 && img->pxl_ptr[c + 2] ==
			-104)
		return (256 * 256 * 256 + 256 * 256 + 256);
	color += img->pxl_ptr[c + 1] * 256;
	color += img->pxl_ptr[c + 2] * 256 * 256;
	return (color);
}
