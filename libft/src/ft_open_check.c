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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../inc/get_next_line.h"

int			ft_open_check(char *filename, int flags, int needed)
{
	int		fd;

	fd = open(filename, flags);
	if (fd < 0 && needed)
		exit(EXIT_FAILURE);
	return (fd);
}
