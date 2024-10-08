/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:59:29 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/22 12:36:07 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		w_check_type_numb_scnfile(t_wind *w, char **tab)
{
	if (ft_isdigit(ft_atoi(tab[w->b.tmpneline])) &&
	(ft_atoi(tab[w->b.tmpneline]) < 0 || ft_atoi(tab[w->b.tmpneline]) > 11))
		exit(ft_comment("Content parsed in file.scn needs to be a\
digit between 0 number and 11."));
}

void		ft_check_count_tab_int(t_wind *w, char *line, int y, char *filename)
{
	char	**tab;

	if ((tab = ft_strsplit(line, ' ')) == NULL)
		exit(ft_print_error_parsing(0, y, filename));
	w->b.tmpneline = 0;
	while (tab[w->b.tmpneline])
	{
		w_check_type_numb_scnfile(w, tab);
		ft_strdel(&tab[w->b.tmpneline++]);
	}
	free(tab);
	if (w->b.tmpneline != w->b.nbrtot_of_line || w->b.nbrtot_of_line < 3)
		exit(ft_comment("file.scn should have the same number of lines \
than elems per line. And a minimum of 3x3 lines"));
}

void		w_insert_tab_int(t_wind *w, char *filename)
{
	int		y;
	int		ret;
	char	*line;
	int		fd;

	y = 0;
	fd = ft_open_check(filename, O_RDONLY, 1);
	w->b.nbrtot_of_line = ft_countline_fd(filename);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_check_count_tab_int(w, line, y, filename);
		ft_strdel(&line);
		y++;
	}
	if (ret < 0)
		exit(ft_print_error_parsing(0, y, filename));
	ft_check_parsing(w, filename);
	insert_file_to_prog(filename, y, w);
	close(fd);
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

	fd = ft_open_check(filename, O_RDONLY, needed);
	if (ft_check_fd(fd, filename, 1))
		exit(1);
	if (ft_strrstr(filename, ".scn"))
		w_insert_tab_int(w, filename);
	else if (ft_strrstr(filename, ".spr"))
	{
		if (set_spr_to_prog(filename, w))
			return (1);
	}
	else if (ft_strrstr(filename, ".par"))
		w_set_par_file(w, filename);
	close(fd);
	return (0);
}
