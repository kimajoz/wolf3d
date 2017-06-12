/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:43:33 by pbillett          #+#    #+#             */
/*   Updated: 2015/12/15 20:16:38 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	int			j;
	size_t		lendst;

	i = 0;
	j = 0;
	lendst = 0;
	while (dst[i] != '\0' && i < size)
	{
		i++;
	}
	lendst = i;
	while (i < (size - 1) && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (lendst < size)
		dst[i] = '\0';
	return (ft_strlen(src) + lendst);
}
