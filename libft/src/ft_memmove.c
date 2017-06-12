/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 19:30:05 by pbillett          #+#    #+#             */
/*   Updated: 2016/01/09 15:58:58 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *dst1;
	unsigned char *src1;

	dst1 = (unsigned char*)dst;
	src1 = (unsigned char*)src;
	if (dst > src)
	{
		dst1 = dst1 + len;
		src1 = src1 + len;
		while (len--)
			*--dst1 = *--src1;
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
