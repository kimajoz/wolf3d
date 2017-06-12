/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 18:00:41 by pbillett          #+#    #+#             */
/*   Updated: 2015/12/03 13:14:02 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void		ft_bzero(void *s, size_t n)
{
	int i;

	i = 0;
	while (i < (int)n)
	{
		((char*)s)[i] = 0;
		i++;
	}
}
