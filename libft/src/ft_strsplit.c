/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 22:23:59 by pbillett          #+#    #+#             */
/*   Updated: 2016/01/08 22:26:28 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int		ft_nbrofpart(char *s, char c)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (s[i])
	{
		if (((s[i] != c && s[i - 1] == c) || (i == 0 && s[i] != c)) && s[i])
		{
			x++;
		}
		i++;
	}
	return (x);
}

static int		ft_lengthofpart(char *s, char c, int x)
{
	int i;
	int y;
	int nbr;

	i = 0;
	y = 0;
	nbr = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i - 1] == c || i == 0))
		{
			while (s[i] && s[i] != c && nbr == x)
			{
				i++;
				y++;
			}
			nbr++;
		}
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
