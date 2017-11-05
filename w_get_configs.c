/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_get_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:28:14 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 20:49:46 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			w_set_initendpos(t_wind *w, char ***tab, int *x, int *y)
{
	int		j;

	j = 0;
	x = 0;
	if (*tab[*x][0] != '#')
	{
		while (*tab[*x])
		{
			if (j == 0)
				w->w.player.init_pos[*x] = ft_atoi(*tab[*x]);
			if (j == 1)
				w->w.player.end_pos[*x] = ft_atoi(*tab[*x]);
			ft_strdel(tab[*x++]);
		}
		j++;
	}
	(*y)++;
	free(tab);
}

void			w_get_config_spr(int fd, t_wind *w)
{
	char	*line;
	char	**tab;
	int		*x;
	int		y;

	y = 0;
	if (!(w->w.player.init_pos = malloc(3 * sizeof(double))))
		exit(0);
	if (!(w->w.player.end_pos = malloc(3 * sizeof(double))))
		exit(0);
	while (get_next_line(fd, &line))
	{
		x = 0;
		tab = ft_strsplit(line, ' ');
		ft_strdel(&line);
		w_set_initendpos(w, &tab, x, &y);
	}
}

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
