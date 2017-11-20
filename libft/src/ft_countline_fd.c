/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countline_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 16:04:49 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/20 16:09:56 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/get_next_line.h"

int			ft_countline_fd(char *filename)
{
	int		fd;
	char	*line;
	int		ret;
	int		y;

	fd = open(filename, O_RDONLY);
	y = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		y++;
		ft_strdel(&line);
	}
	close(fd);
	if (ret < 0)
		exit(ft_comment("File not found or wrong parsing in file."));
	return (y);
}
