/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_create_spr_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:06:28 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/22 12:35:21 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		create_spr_map(t_wind *w)
{
	int		y;
	int		x;

	if (!(w->w.tab_int_spr =
	malloc((w->b.nbrtot_of_line) * sizeof(t_sprite *))))
		exit(1);
	y = 0;
	while (y < w->b.nbrtot_of_line)
	{
		if (!(w->w.tab_int_spr[y] =
		malloc(w->b.nbr_elem_line[0] * sizeof(t_sprite))))
			exit(1);
		x = 0;
		while (x < w->b.nbr_elem_line[0])
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

void		w_check_spr_inmap_anddigit(t_wind *w, char **tab)
{
	int		i;

	i = 0;
	while (i < 1)
	{
		if (ft_isnumber(tab[i])
		&& (ft_atoi(tab[i]) < 7 && ft_atoi(tab[i]) > 0))
			i++;
		else
			exit(ft_comment("wrong number of type of sprites in .spr file, \
or not digit numbers."));
	}
	while (i < 3)
	{
		if (ft_isnumber(tab[i])
		&& (ft_atoi(tab[i]) < w->b.nbrtot_of_line ||
		ft_atoi(tab[i]) < w->b.nbr_elem_line[0]) && ft_atoi(tab[i]) >= 0)
			i++;
		else
			exit(ft_comment("wrong number of elem in .spr file. \
Not a digit numbers, or not inside the map."));
	}
	w->w.tab_int_spr[ft_atoi(tab[2])][ft_atoi(tab[1])].num = ft_atoi(tab[0]);
	w->w.tab_int_spr[ft_atoi(tab[2])][ft_atoi(tab[1])].block =
	w->w.sprite[ft_atoi(tab[0])].block;
}

void		w_setsprcoordfile_tosprmap(int fd, t_wind *w)
{
	char	*line;
	int		x;
	char	**tab;
	int		ret;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		x = 0;
		if (line[0] != '#')
		{
			if ((tab = ft_strsplit(line, ' ')) == NULL)
				exit(1);
			w_check_spr_inmap_anddigit(w, tab);
			while (tab[x])
				ft_strdel(&tab[x++]);
			free(tab);
			w->w.nbtotsprprog++;
		}
		ft_strdel(&line);
	}
	if (ret < 0)
		exit(ft_comment("Cannot read .spr file. Please check path"));
}

int			set_spr_to_prog(char *filename, t_wind *w)
{
	int		fd1;

	fd1 = open(filename, O_RDONLY);
	w->w.info.spr = 1;
	init_sprites(w);
	w->w.sprnbvis = 0;
	create_spr_map(w);
	w->w.nbtotsprprog = 0;
	w_setsprcoordfile_tosprmap(fd1, w);
	if (!(w->w.visiblespr = malloc(w->w.nbtotsprprog * sizeof(t_sprite))))
		exit(1);
	return (0);
}
