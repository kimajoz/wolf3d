/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 22:23:59 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/28 17:29:45 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int				ft_nbrofpart(char *s, char c)
{
	int			i;
	int			x;

	i = 0;
	x = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c) && s[i])
		{
			x++;
		}
		i++;
	}
	return (x);
}

static int		ft_lengthofpart(char *s, char c, int maxnb_elem)
{
	int i;
	int y;
	int nbr;

	i = 0;
	y = 0;
	nbr = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			while (s[i] && s[i] != c && nbr == maxnb_elem)
			{
				i++;
				y++;
			}
			nbr++;
		}
		if (s[i])
			i++;
	}
	return (y);
}

static char		*ft_contentofpart(char *s, char c, int x)
{
	int			i;
	int			y;
	int			nbr;
	char		*cont;

	i = 0;
	y = 0;
	nbr = 0;
	cont = ft_memalloc(sizeof(char) * (ft_lengthofpart(s, c, x) + 1));
	while (s[i])
	{
		if (s[i] != c && nbr == x)
		{
			cont[y] = s[i];
			y++;
		}
		if (i > 0 && s[i] == c && s[i - 1] != c)
		{
			nbr++;
		}
		i++;
	}
	cont[y] = '\0';
	return (cont);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**strtot;
	size_t		x;
	size_t		i;

	if (!c)
		return ((char **)s);
	x = ft_nbrofpart((char*)s, c);
	i = 0;
	strtot = ft_memalloc(sizeof(char *) * (x + 1));
	if (strtot == NULL)
		return (NULL);
	while (i < x)
	{
		strtot[i] = ft_contentofpart((char*)s, c, i);
		i++;
	}
	strtot[i] = NULL;
	return (strtot);
}
