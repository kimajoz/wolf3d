/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:17:23 by pbillett          #+#    #+#             */
/*   Updated: 2017/05/24 12:50:07 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define CUBESIZE	64

void			wolf3d(t_wind *w)
{
	t_camera	cam;
	t_viewplane	vp;
	t_viewplane	vpc;
	int			i;

	i = 0;
	vp.w = 320;
	vp.h = 200;
	cam.fov = 60;
	cam.pos.y = CUBESIZE / 2;
	cam.anglebetrays = cam.fov / vp.w;
	vpc.w = vp.w / 2;
	vpc.h = vp.h / 2;
	vp.dist = vpc.w / tan(cam.fov/2);

	while (i < w->b.nbrtot_of_line)
	{
		/*ft_putstr("nub element on line:");
		ft_putnbr(w->b.nbr_elem_line[i]);
		ft_putchar('\n');*/
		ft_putlstnbr(w->b.tab_int[i], w->b.nbr_elem_line[i]);
		ft_putchar('\n');
		i++;
	}
}
