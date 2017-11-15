/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_does_file_exist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:51:35 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/15 14:52:35 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

int					ft_does_file_exist(const char *filename)
{
	struct stat		st;
	int				result;

	result = stat(filename, &st);
	return (result == 0);
}
