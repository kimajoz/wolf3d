/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:26:55 by pbillett          #+#    #+#             */
/*   Updated: 2015/12/01 18:31:42 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		p;

	i = 0;
	p = 0;
	if (s2[0] == '\0')
		return ((char*)s1);
	while (s1[i])
	{
		if (s1[i] == s2[0])
		{
			p = 0;
			while (s1[i + p] == s2[p] && s1[i])
			{
				if (s2[p + 1] == '\0')
					return (((char*)s1) + i);
				p++;
			}
		}
		i++;
	}
	return (NULL);
}
