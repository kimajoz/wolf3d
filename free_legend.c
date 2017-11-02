/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_legend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:23:46 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/02 15:32:46 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int					w_insidemap(int x, int y, t_wind *w)
{
	if ((y >= 0 && y < w->b.nbrtot_of_line) &&
	(x >= 0 && x < w->b.nbr_elem_line[0]))
		return (1);
	return (0);
}

void				w_mlibx_putint(int i, int row, int column, t_wind *w)
{
	char			*str;

	str = ft_itoa(i);
	mlibx_putstring(str, row, column, w);
	if (str)
		free(str);
}

void				legend(t_wind *w)
{
	w->w.legend = malloc(sizeof(char *) * NBLEGEND + 1);
	w->w.legend[0] = ft_itoa(w->w.player.health);
	w->w.legend[1] = ft_itoa(w->w.player.ammunition);
	w->w.legend[2] = ft_itoa(w->w.player.object);
	w->w.legend[3] = ft_itoa(w->w.player.totalscore);
	w->w.legend[4] = ft_itoa(w->w.info.ray_minimap);
	w->w.legend[5] = ft_itoa(w->w.info.bg);
	w->w.legend[6] = ft_itoa(w->w.info.texture);
	w->w.legend[7] = ft_itoa(w->w.info.raynumb);
	w->w.legend[8] = ft_itoa(w->w.player.points);
	w->w.legend[9] = ft_itoa(w->w.player.kills);
	w->w.legend[10] = ft_itoa(w->w.player.health);
	w->w.legend[11] = ft_itoa(TIMEOUT_GAME - (int)w->w.player.timeout);
	w->w.legend[12] = ft_itoa((int)w->w.player.points + w->w.player.kills +
		w->w.player.health + (TIMEOUT_GAME - (int)w->w.player.timeout));
	w->w.legend[13] = ft_itoa(w->cam.pos.x);
}

void				free_legend(t_wind *w)
{
	int				i;

	i = 0;
	while (i <= NBLEGEND)
		ft_strdel(&w->w.legend[i++]);
	if (w->w.legend)
		free(w->w.legend);
}
