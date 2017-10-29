/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_create_spr_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:06:28 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/28 18:09:45 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		create_spr_map(t_wind *w)
{
	int		y;
	int		x;

	w->w.tab_int_spr = malloc(w->b.nbrtot_of_line * sizeof(t_sprite *));
	y = 0;
	while (y < w->b.nbrtot_of_line)
	{
		w->w.tab_int_spr[y] = malloc(w->b.nbr_elem_line[3] * sizeof(t_sprite));
		x = 0;
		while (x < w->b.nbr_elem_line[3])
		{
			w->w.tab_int_spr[y][x].num = 0;
			w->w.tab_int_spr[y][x].posx = x;
			w->w.tab_int_spr[y][x].posy = y;
			w->w.tab_int_spr[y][x].vis = 0;
			w->w.tab_int_spr[y][x].block = 0;
			x++;
		}
		y++;
	}
}

void		w_setsprcoordfile_tosprmap(int fd, t_wind *w)
{
	char	*line;
	int		x;
	char	**tab;

	while (get_next_line(fd, &line))
	{
		x = 0;
		if (line[0] != '#')
		{
			tab = ft_strsplit(line, ';');
			w->w.tab_int_spr[ft_atoi(tab[2])][ft_atoi(tab[1])].num =
				ft_atoi(tab[0]);
			w->w.tab_int_spr[ft_atoi(tab[2])][ft_atoi(tab[1])].block =
				w->w.sprite[ft_atoi(tab[0])].block;
			while (tab[x])
				ft_strdel(&tab[x++]);
			free(tab);
			w->w.nbtotsprprog++;
		}
		ft_strdel(&line);
	}
	//free_tablst(tab);
}

int			set_spr_to_prog(int fd, char *filename, t_wind *w)
{
	if (ft_check_fd(fd, filename, 0))
	{
		w->w.info.spr = 0;
		return (0);
	}
	w->w.info.spr = 1;
	init_sprites(w);
	w->w.sprnbvis = 0;
	create_spr_map(w);
	w->w.nbtotsprprog = 0;
	w_setsprcoordfile_tosprmap(fd, w);
	w->w.visiblespr = malloc(w->w.nbtotsprprog * sizeof(t_sprite));
	return (0);
}
