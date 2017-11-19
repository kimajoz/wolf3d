/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:42:16 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/14 19:47:19 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/get_next_line.h"

int			ft_check_fd(int fd, char *filename, int optional)
{
	char	*line;
	int		ret;

	while ((ret = get_next_line(fd, &line)) < 0)
	{
		if (ret < 0)
		{
			ft_putstr(filename);
			ft_putstr(" file not here, or with wrong parsing. (Please see examples in maps folder).");
			if (optional)
				ft_putendl("");
			return (1);
		}
		//if (!line)
		ft_strdel(&line);
	}
	//if (ret < 0)
		//exit(ft_comment("File not found or wrong parsing in file."));
	return (0);
}
