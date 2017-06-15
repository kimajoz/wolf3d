/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:43:29 by pbillett          #+#    #+#             */
/*   Updated: 2016/12/27 13:48:05 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void			draw_circle(t_wind *w, t_point centp, int rayon, char *hexcol)
{
	int			i;
	double		i_rad;
	t_point		pos;

	i = 0;
	if (ft_strcmp(hexcol, "no") == 0)
		hexcol = w->p.color.hexa_default;
	while (i < 360)
	{
		i_rad = ft_degree_to_radian(i);
		pos.x = ((double)rayon * cos(i_rad)) + centp.x;
		pos.y = ((double)rayon * sin(i_rad)) + centp.y;
		pos.z = centp.z;
		mlibx_draw_pixel(w, pos.x, pos.y, hexcol);
		i++;
	}
}

void			draw_circlef(t_wind *w, t_point centp, int rayon, char *hexcol)
{
	int			r;

	r = 0;
	while (r < rayon)
		draw_circle(w, centp, r++, hexcol);
}
