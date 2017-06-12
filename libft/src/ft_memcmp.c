/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:17:08 by pbillett          #+#    #+#             */
/*   Updated: 2015/11/30 12:34:28 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int					i;
	unsigned char		*str1;
	unsigned char		*str2;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	i = 0;
	while (i < (int)n)
	{
		if ((str1[i]) != (str2[i]))
			return ((str1)[i] - (str2)[i]);
		i++;
	}
	return (0);
}
