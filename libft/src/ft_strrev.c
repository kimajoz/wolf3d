/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 14:17:15 by pbillett          #+#    #+#             */
/*   Updated: 2016/10/18 17:32:06 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strrev(char *str)
{
	int		i;
	int		a;
	char	c;

	a = 0;
	i = ft_strlen(str);
	i--;
	while (i >= a)
	{
		c = str[i];
		str[i] = str[a];
		str[a] = c;
		a++;
		i--;
	}
	return (str);
}
