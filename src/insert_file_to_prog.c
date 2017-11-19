/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_file_to_prog.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 16:03:27 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/15 16:04:43 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		w_set_init_endpos(t_wind *w, char **tab, int j)
{
	if (j == 0)
	{
		w->w.player.init_pos.x = ft_atoi(tab[0]);
		w->w.player.init_pos.y = ft_atoi(tab[1]);
		w->w.player.init_pos.z = ft_atoi(tab[2]);
	}
	if (j == 1)
	{
		w->w.player.end_pos.x = ft_atoi(tab[0]);
		w->w.player.end_pos.y = ft_atoi(tab[1]);
		w->w.player.end_pos.z = ft_atoi(tab[2]);
	}
}

void		ft_check_parsing_param_type(t_wind *w, char **tab)
{
	int		i;

	i = 0;
	while (i < 2)
	{
		if (ft_isnumber(tab[i])
		&& (ft_atoi(tab[i]) < w->b.nbrtot_of_line
		|| ft_atoi(tab[i]) < w->b.nbr_elem_line[0])
		&& ft_atoi(tab[i]) >= 0)
			i++;
		else
			exit(ft_comment("wrong number in .par file, or not digit numbers. \
Not inside the map."));
	}
	while (i < 3)
	{
		if (ft_isnumber(tab[i])
		&& ft_atoi(tab[i]) < 360
		&& ft_atoi(tab[i]) >= 0)
			i++;
		else
			exit(ft_comment("wrong number in .par file for rotation, \
or not digit numbers."));
	}
}

void		set_param_to_prog(int fd, t_wind *w, int j, int y)
{
	char	*line;
	char	**tab;
	int		x;

	while (get_next_line(fd, &line) > 0)
	{
		x = 0;
		if (line[0] != '#')
		{
			if ((tab = ft_strsplit(line, ' ')) == NULL)
				exit(1);
			ft_check_parsing_param_type(w, tab);
			w_set_init_endpos(w, tab, j);
			while (tab[x])
				ft_strdel(&tab[x++]);
			free(tab);
			j++;
		}
		ft_strdel(&line);
		y++;
	}
}

void		init_mem_prog(t_wind *w, int y)
{
	if (!(w->b.tab_int = malloc((y + 1) * sizeof(int *))))
		exit(0);
	if (!(w->b.nbr_elem_line = malloc((y + 1) * sizeof(int *))))
		exit(0);
}

void		insert_file_to_prog(char *filename, int y, t_wind *w)
{
	char	*line;
	char	**tab;
	int		x;
	int		len;
	int		fd;

	init_mem_prog(w, y);
	y = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		tab = ft_strsplit(line, ' ');
		len = ft_nbrofpart(line, ' ');
		if (!(w->b.tab_int[y] = malloc((len + 1) * sizeof(int))))
			exit(0);
		x = 0;
		while (tab[x])
		{
			w->b.tab_int[y][x] = ft_atoi(tab[x]);
			ft_strdel(&tab[x++]);
		}
		w->b.nbr_elem_line[y++] = x;
		free(tab);
		ft_strdel(&line);
	}
}
