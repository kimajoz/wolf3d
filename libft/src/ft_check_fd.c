/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:42:16 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/09 19:24:22 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/get_next_line.h"

int			ft_check_fd(int fd, char *filename, int needed)
{
	char	*line;
	int		ret;

	while ((ret = get_next_line(fd, &line)) < 0)
	{
		ft_putstr("File not found or empty file: ");
		ft_putstr(filename);
		ft_comment("ft_check_fd 01");
		if (!needed)
			ft_putstr(" (Optional file)");
		ft_putchar('\n');
		ft_comment("ft_check_fd 02");
		if (fd == -1)
			return (1);
		ft_putnbr(fd);
		ft_comment("ft_check_fd 03");
		if (line)
			ft_strdel(&line);
		ft_comment("ft_check_fd 04");
	}
	if (ret < 0)
		exit(ft_comment("File not found or wrong parsing in file."));
	return (0);
}
