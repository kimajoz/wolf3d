/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlibx_draw_dot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:33:46 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 16:33:50 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void		mlibx_draw_dot(t_wind *w, int x, int y, int color)
{
	char	b;
	char	g;
	char	r;
	int		i;

	if (color == 256 * 256 * 256 + 256 * 256 + 256)
		return ;
	i = (w->img.size_line * y) + (x * (w->img.bpp / 8));
	b = color % 256;
	g = (color / 256) % 256;
	r = (color / 256 / 256) % 256;
	w->img.pxl_ptr[i] = b;
	w->img.pxl_ptr[i + 1] = g;
	w->img.pxl_ptr[i + 2] = r;
}
