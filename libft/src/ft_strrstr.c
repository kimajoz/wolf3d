/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:26:55 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/14 18:05:56 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strrstr(const char *s1, const char *s2)
{
	char	*s1r;
	char	*s2r;
	int		i;
	int		p;

	s1r = ft_strrev((char *)s1);
	s2r = ft_strrev(ft_strdup((char *)s2));
	i = 0;
	if (s2r[0] == '\0')
		return ((char*)s1);
	if (s1r[0] == s2r[0])
	{
		p = 0;
		while (s1r[i] == s2r[p] && s1r[i])
		{
			if (s2r[p + 1] == '\0')
			{
				s1 = ft_strrev((char*)s1);
				ft_strdel(&s2r);
				return ((char *)s1 + (ft_strlen(s1) - (i + 1)));
			}
			p++;
			i++;
		}
	}
	ft_strdel(&s2r);
	return (NULL);
}
