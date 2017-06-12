/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 16:38:11 by pbillett          #+#    #+#             */
/*   Updated: 2015/12/07 16:52:37 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*strtot;

	i = 0;
	j = 0;
	strtot = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (strtot == NULL)
		return (NULL);
	while (s1[i])
	{
		strtot[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		strtot[i] = s2[j];
		i++;
		j++;
	}
	strtot[i] = '\0';
	return (strtot);
}
