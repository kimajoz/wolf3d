/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:06:15 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/06 22:13:56 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_print_error_parsing(int x, int y)
{
	ft_putstr("wrong file type, wrong parsing, ");
	ft_putstr("please check number of elem(now ");
	ft_putnbr(x);
	ft_putstr(" -> needs ");
	ft_putnbr(MAPLEN);
	ft_putstr(") on line ");
	ft_putnbr(y + 1);
	ft_putstr(".");
	ft_putstr("\n");
	return (1);
}

int			ft_print_error_type_parsing(int x, int y)
{
	ft_putstr("wrong file type, wrong parsing, ");
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

int			ft_check_parsing(char *filename)
{
	int		fd;
	char	**tab;
	char	*line;
	int		i;
	int		y;

	y = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		tab = ft_strsplit(line, ' ');
		i = 0;
		if (line[0] != '#')
		{
			while (tab[i])
				ft_strdel(&tab[i++]);
			free(tab);
			if (i != MAPLEN)
				return (ft_print_error_parsing(i, y));
		}
		y++;
	}
	return (0);
}
