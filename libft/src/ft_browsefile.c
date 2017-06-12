/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browsefile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:37:09 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/19 16:36:34 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/get_next_line.h"

static int	**save_line(char *line, int **y, int **x, int **tab_int)
{
	char	**tab;

	tab = NULL;
	tab_int[(**y)] = malloc(ft_strlen(line) * sizeof(int));
	tab = ft_strsplit(line, ' ');
	ft_strdel(&line);
	(**x) = 0;
	while (tab[(**x)])
	{
		tab_int[(**y)][(**x)] = ft_atoi(tab[(**x)]);
		ft_strdel(&tab[(**x)]);
		(**x)++;
	}
	free(tab);
	(**y)++;
	return (tab_int);
}

static int	check_fd(int fd)
{
	char	*line;

	if (fd == -1 || !get_next_line(fd, &line))
	{
		ft_putstr("empy file, please check source_file\n");
		return (1);
	}
	return (0);
}

int			**browsefile(char *filename, int *y, int *x)
{
	int		fd;
	int		fd1;
	char	*line;
	int		**tab_int;

	fd = open(filename, O_RDONLY);
	fd1 = open(filename, O_RDONLY);
	if (check_fd(fd1) == 1)
		return (NULL);
	tab_int = NULL;
	(*y) = 0;
	while (get_next_line(fd1, &line))
	{
		ft_strdel(&line);
		(*y)++;
	}
	tab_int = malloc(((*y) + 1) * sizeof(int *));
	(*y) = 0;
	while (get_next_line(fd, &line))
		save_line(line, &y, &x, tab_int);
	close(fd);
	close(fd1);
	return (tab_int);
}
