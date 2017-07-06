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

int			**rt_file(char *filename, int y, t_wind *w)
{
	int		fd;
	int		fd1;
	char	*line;
	int		**tab_int;

	fd = open(filename, O_RDONLY);
	fd1 = open(filename, O_RDONLY);
	if (check_fd(fd1) == 1)
		return (NULL);
	y = 0;
	while (get_next_line(fd1, &line))
	{
		ft_strdel(&line);
		y++;
	}
	w->b.nbrtot_of_line = y;
	if (ft_check_parsing(filename) == 1)
		return (0);
	tab_int = insert_file_to_prog(fd, y, w);
	close(fd1);
	close(fd);
	return (tab_int);
}
