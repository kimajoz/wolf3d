/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:06:15 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/28 17:10:28 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_print_error_parsing(int x, int y)
{
	ft_putstr("wrong parsing file, ");
	ft_putstr("please check number of elem(now ");
	ft_putnbr(x);
	ft_putstr(" -> needs ");
	ft_putstr(" lenght of the line ");
	ft_putstr(") on line ");
	ft_putnbr(y + 1);
	ft_putstr(".");
	ft_putstr("\n");
	return (1);
}

int			ft_print_error_type_parsing(int x, int y)
{
	ft_putstr("wrong type in parsing file, ");
	ft_putstr("please check type of character ");
	ft_putnbr(x);
	ft_putstr(" on line ");
	ft_putnbr(y + 1);
	ft_putstr(".");
	ft_putstr("\n");
	return (1);
}

int			ft_numdigit(char *n)
{
	int		i;

	i = 0;
	while (n[i])
	{
		if (ft_isdigit(n[i]) != 1 && n[i] != '-')
			return (1);
		i++;
	}
	return (0);
}

void		ft_check_parsing_param(char *filename)
{
	int		fd;
	char	**tab;
	char	*line;
	int		i;
	int		y;

	y = 0;
	fd = open(filename, O_RDONLY);
	if (ft_check_fd(fd, filename, 1))
		exit(EXIT_FAILURE);
	while (get_next_line(fd, &line))
	{
		i = 0;
		if (line[0] != '#')
		{
			tab = ft_strsplit(line, ' ');
			while (tab[i])
				ft_strdel(&tab[i++]);
			free(tab);
			if (i != 3)
				exit(ft_print_error_parsing(i, y));
		}
		ft_strdel(&line);
		y++;
	}
}

void		ft_check_parsing(t_wind *w, char *filename)
{
	int		fd;
	char	**tab;
	char	*line;
	//char	*linecp;
	int		i;
	int		y;
	//int		len;

	y = 0;
	//ft_putendl("before rt_parsing");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit (1);
	while (get_next_line(fd, &line))
	{
		//linecp = malloc(sizeof(char) * ft_strlen(line) + 1);
		//ft_strcpy(linecp, line);
		i = 0;
		if (line[0] != '#')
		{
			//len = ft_nbrofpart(line, ' ');
			//tab = malloc(len * sizeof(char *));
			tab = ft_strsplit(line, ' ');
			while (tab[i])
				ft_strdel(&tab[i++]);
			free(tab);
			if (i != w->b.tmpneline)
				exit(ft_print_error_parsing(i, y));
		}
		ft_strdel(&line);
		y++;
	}
	ft_putendl("after rt_parsing");
	//ft_strdel(&line);
	//free_tablst(tab);
}
