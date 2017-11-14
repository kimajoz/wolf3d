/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:26:55 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/14 19:41:49 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strrstr(const char *s1, const char *s2)
{
	char	*s1r;
	char	*s2r;
	int		i;
	int		p;

	ft_comment("enter ft_strrstr");
	s1r = ft_strrev((char *)s1);
	s2r = ft_strrev(ft_strdup((char *)s2));
	ft_comment("enter ft_strrstr rev ok");
	ft_comment("enter s1r");
	ft_comment(s1r);
	ft_comment("enter s2r");
	ft_comment(s2r);
	i = 0;
	if (s2r[0] == '\0')
		return ((char*)s1);
	ft_comment("enter ft_strrstr rev ok 0");
	if (s1r[0] == s2r[0])
	{
		ft_comment("enter ft_strrstr rev ok 1");
		p = 0;
		while (s1r[i] == s2r[p] && s2r[i])
		{
			ft_comment("enter ft_strrstr rev ok 2");
			ft_putchar(s2r[p]);
			if (s2r[p + 1] == '\0')
			{
				ft_comment("enter ft_strrstr rev ok 3");
				s1 = ft_strrev((char*)s1);
				ft_strdel(&s2r);
				ft_comment("check ft_strrstr");
				ft_comment((char *)s1);
				ft_comment((char *)s1 + (ft_strlen(s1) - (i + 1)));
				return ((char *)s1 + (ft_strlen(s1) - (i + 1)));
			}
			p++;
			i++;
		}
	}
	s1 = ft_strrev((char*)s1);
	ft_strdel(&s2r);
	return (NULL);
}
