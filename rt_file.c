/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:06:32 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/30 12:48:59 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		free_tablst(char **tab)
{
	int		x;

	x = 0;
	while (tab[x])
		ft_strdel(&tab[x++]);
	ft_strdel(tab);
}

void		set_param_to_prog(int fd, t_wind *w, int j, int y)
{
	char	*line;
	char	**tab;
	int		x;

	w->w.player.init_pos = malloc(3 * sizeof(double));
	w->w.player.end_pos = malloc(3 * sizeof(double));
	while (get_next_line(fd, &line))
	{
		x = 0;
		if (line[0] != '#')
		{
			tab = ft_strsplit(line, ' ');
			while (tab[x])
			{
				if (j == 0)
					w->w.player.init_pos[x] = ft_atoi(tab[x]);
				if (j == 1)
					w->w.player.end_pos[x] = ft_atoi(tab[x]);
				ft_strdel(&tab[x++]);
			}
			free(tab);
			j++;
		}
		ft_strdel(&line);
		y++;
	}
}

int			**insert_file_to_prog(int fd, int y, t_wind *w)
{
	char	*line;
	char	**tab;
	int		**tab_int;
	int		x;
	int		len;

	tab_int = malloc((y + 1) * sizeof(int *));
	w->b.nbr_elem_line = malloc((y + 1) * sizeof(int *));
	y = 0;
	while (get_next_line(fd, &line))
	{
		tab = ft_strsplit(line, ' ');
		len = ft_nbrofpart(line, ' ');
		tab_int[y] = malloc(len * sizeof(int));
		x = 0;
		while (tab[x])
		{
			tab_int[y][x] = ft_atoi(tab[x]);
			ft_strdel(&tab[x++]);
		}
		w->b.nbr_elem_line[y++] = x;
		free(tab);
		ft_strdel(&line);
	}
	w->b.nbr_of_line = y;
	return (tab_int);
}

void		w_insert_tab_int(t_wind *w, int *fd, char **line, char **filename)
{
	int		fd1;
	int		y;
	char	**tab;

	fd1 = open(*filename, O_RDONLY);
	if (ft_check_fd(fd1, *filename, w->b.needed) == 1)
		exit(EXIT_FAILURE);
	y = 0;
	if (ft_strstr(*filename, "scn"))
	{
		while (get_next_line(fd1, line))
		{
			tab = ft_strsplit(*line, ' ');
			w->b.tmpneline = 0;
			while (tab[w->b.tmpneline])
				ft_strdel(&tab[w->b.tmpneline++]);
			free(tab);
			ft_strdel(line);
			y++;
		}
		w->b.nbrtot_of_line = y + 1;
		ft_check_parsing(w, *filename);
		w->b.tab_int = insert_file_to_prog(*fd, y, w);
	}
	close(fd1);
}

int			rt_file(char *filename, t_wind *w, int needed)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	w->b.needed = needed;
	if (ft_strstr(filename, "scn"))
		w_insert_tab_int(w, &fd, &line, &filename);
	if (ft_strstr(filename, "spr"))
		set_spr_to_prog(fd, filename, w);
	else if (ft_strstr(filename, "par"))
	{
		ft_check_parsing_param(filename);
		set_param_to_prog(fd, w, 0, 0);
	}
	close(fd);
	return (1);
}
