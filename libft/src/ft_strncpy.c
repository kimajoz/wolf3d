/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 13:11:19 by pbillett          #+#    #+#             */
/*   Updated: 2016/01/05 19:55:39 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t i;

	i = 0;
	ft_bzero(dst, n);
	while (i < n && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (ft_strlen(src) <= n)
		dst[i] = '\0';
	return (dst);
}
