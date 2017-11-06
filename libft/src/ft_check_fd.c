/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:42:16 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 16:42:20 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/get_next_line.h"

int			ft_check_fd(int fd, char *filename, int needed)
{
	char	*line;
	int		ret;

	while ((ret = get_next_line(fd, &line) > 0))
	{
		ft_putstr("File not found or empty file: ");
		ft_putstr(filename);
		if (!needed)
			ft_putstr(" (Optional file)");
		ft_putchar('\n');
		if (fd == -1)
			return (1);
		ft_strdel(&line);
	}
	if (ret < 0)
		exit(ft_comment("File not found or wrong parsing in file."));
	return (0);
}
