/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:46:08 by pbillett          #+#    #+#             */
/*   Updated: 2016/01/09 18:23:48 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	int			p;
	char		*str;

	i = 0;
	p = 0;
	str = (char*)s1;
	if (s2[0] == '\0')
		return (str);
	while (i < n && s1[i] && s2[p])
	{
		if (str[i] == ((char*)s2)[0])
		{
			while (str[i + p] == s2[p] && ((i + p) < n) && s1[i] && s2[p])
			{
				p++;
			}
			if (s2[p] == '\0')
			{
				return (str + i);
			}
		}
		i++;
	}
	return (NULL);
}
