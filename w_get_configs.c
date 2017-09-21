/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_get_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:28:14 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/21 17:46:44 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			w_get_config_walls()
{
	


}


void			w_get_config_spr(int fd, t_wind *w)
{
	char	*line;
	char	**tab;
	int		x;
	int		j;
	int		y;

	w->w.player.init_pos = malloc(3 * sizeof(double));
	w->w.player.end_pos = malloc(3 * sizeof(double));
	j = 0;
	y = 0;
	while (get_next_line(fd, &line))
	{
		tab = ft_strsplit(line, ' ');
		ft_strdel(&line);
		x = 0;
		if (tab[x][0] != '#')
		{
			while (tab[x])
			{
				if (j == 0)
					w->w.player.init_pos[x] = ft_atoi(tab[x]);
				if (j == 1)
					w->w.player.end_pos[x] = ft_atoi(tab[x]);
				ft_strdel(&tab[x++]);
			}
			j++;
		}
		y++;
		free(tab);
	}
}


void			w_get_config_guns()
{
	


}

void			w_get_configs()
{
	


}
