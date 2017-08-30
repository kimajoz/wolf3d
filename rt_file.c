/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:06:32 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/06 23:09:57 by pbillett         ###   ########.fr       */
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
			w->w.tab_int_spr[y][x++].vis = 0;
			w->w.tab_int_spr[y][x++].num = 0;
		}
		y++;
	}
}

int			get_spr_block_by_type(t_wind *w, int num_spr)
{
	int		boolb;

	boolb = 1; //(we cannot go through sprites by default).
	while ( < w->)
	{

	}
	return (boolb);
}

void		set_spr_to_prog(int fd, t_wind *w)
{
	char	*line;
	char	**tab;
	int		x;
	int		j;

	init_sprites(w);
	w->w.sprnbvis = 0;
	create_spr_map(w);
	//w_clear_vis_sprites(w); //Set sprite visibility to 0 for first time
	j = 0;
	// We set the sprites inside the map:
	while (get_next_line(fd, &line))
	{
		//w->w.tab_int_spr[j] = malloc(w->b.nbr_elem_line[3] * sizeof(int));
		tab = ft_strsplit(line, ';');
		ft_strdel(&line);
		x = 0;
		if (tab[x][0] != '#')
		{
			w->w.tab_int_spr[ft_atoi(tab[2])][ft_atoi(tab[1])].num = ft_atoi(tab[0]);
			w->w.tab_int_spr[ft_atoi(tab[2])][ft_atoi(tab[1])].block = get_spr_block_by_type(w, tab[0]);
			while (tab[x])
				ft_strdel(&tab[x++]);
			j++;
		}
		free(tab);
	}
}

void		set_param_to_prog(int fd, t_wind *w)
{
	char	*line;
	char	**tab;
	int		x;
	int		j;
	int		y;

	w->w.player.init_pos = malloc(3 * sizeof(double));
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
				ft_strdel(&tab[x++]);
			}
			j++;
		}
		y++;
		free(tab);
	}
}

int			**insert_file_to_prog(int fd, int y, t_wind *w)
{
	char	*line;
	char	**tab;
	int		**tab_int;
	int		x;

	tab_int = malloc((y + 1) * sizeof(int *));
	w->b.nbr_elem_line = malloc((y + 1) * sizeof(int *));
	y = 0;
	while (get_next_line(fd, &line))
	{
		tab_int[y] = malloc(ft_strlen(line) * sizeof(int));
		tab = ft_strsplit(line, ' ');
		ft_strdel(&line);
		x = 0;
		while (tab[x])
		{
			tab_int[y][x] = ft_atoi(tab[x]);
			ft_strdel(&tab[x++]);
		}
		w->b.nbr_elem_line[y++] = x;
		free(tab);
	}
	w->b.nbr_of_line = y;
	return (tab_int);
}

int			**rt_file(char *filename, int y, t_wind *w, int needed)
{
	int		fd;
	int		fd1;
	char	*line;
	int		**tab_int;

	fd = open(filename, O_RDONLY);
	fd1 = open(filename, O_RDONLY);
	if (ft_check_fd(fd1, filename, needed) == 1)
		return (NULL);
	y = 0;
	if (ft_strstr(filename, "scn"))
	{
		while (get_next_line(fd1, &line))
		{
			ft_strdel(&line);
			y++;
		}
		w->b.nbrtot_of_line = y + 1;
		if (ft_check_parsing(filename) == 1)
			return (NULL);
		tab_int = insert_file_to_prog(fd, y, w);
	}
	else if (ft_strstr(filename, "spr"))
		set_spr_to_prog(fd, w);
	else if (ft_strstr(filename, "par"))
	{
		if (ft_check_parsing_param(filename) == 1)
			return (NULL);
		set_param_to_prog(fd, w);
	}
	close(fd1);
	close(fd);
	return (tab_int);
}
