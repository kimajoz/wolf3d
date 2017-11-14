/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:59:29 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/14 20:18:58 by pbillett         ###   ########.fr       */
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

	while (get_next_line(fd, &line))
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
		if (!(w->b.tab_int[y] = malloc((len +1) * sizeof(int))))
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

void		w_insert_tab_int(t_wind *w, int *fd, char **line, char **filename)
{
	int		y;
	char	**tab;
	int		ret;

	y = 0;
	while ((ret = get_next_line(*fd, line)) > 0)
	{
		if ((tab = ft_strsplit(*line, ' ')) == NULL)
			exit(ft_print_error_parsing(0, y));
		w->b.tmpneline = 0;
		while (tab[w->b.tmpneline])
		{
			if (ft_isdigit(ft_atoi(tab[w->b.tmpneline])) &&
(ft_atoi(tab[w->b.tmpneline]) < 0 || ft_atoi(tab[w->b.tmpneline]) > 11))
				exit(ft_comment("Content parsed in file.scn needs to be a\
digit between 0 number and 11."));
			ft_strdel(&tab[w->b.tmpneline++]);
		}
		free(tab);
		ft_strdel(line);
		y++;
	}
	if (ret < 0)
		exit(ft_print_error_parsing(0, y));
	w->b.nbrtot_of_line = y;
	ft_check_parsing(w, *filename);
	insert_file_to_prog(*filename, y, w);
	close(*fd);
}

void		w_set_par_file(t_wind *w, char *filename)
{
	int		fd1;

	ft_check_parsing_param(filename);
	fd1 = open(filename, O_RDONLY);
	set_param_to_prog(fd1, w, 0, 0);
	w->cam.pos.x = w->w.player.init_pos.x + 0.5;
	w->cam.pos.z = w->w.player.init_pos.y + 0.5;
	w->cam.rot.y = w->w.player.init_pos.z;
	w->w.bolpar = 1;
	close(fd1);
}

int			w_file(char *filename, t_wind *w, int needed)
{
	int		fd;
	char	*line;

	ft_comment("enter rt_file");
	ft_comment(filename);
	fd = ft_open_check(filename, O_RDONLY, needed);
	if (ft_check_fd(fd, filename, 1))
		exit(1);
	if (ft_strrstr(filename, ".scn"))
		w_insert_tab_int(w, &fd, &line, &filename);
	else if (ft_strrstr(filename, ".spr"))
	{
		ft_comment(".spr file open");
		if (set_spr_to_prog(filename, w))
			return (1);
	}
	else if (ft_strrstr(filename, ".par"))
		w_set_par_file(w, filename);
	close(fd);
	return (0);
}
