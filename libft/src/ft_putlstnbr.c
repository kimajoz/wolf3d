/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlstnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 20:18:49 by pbillett          #+#    #+#             */
/*   Updated: 2016/02/24 20:36:03 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_putlstnbr(int *lstnbr, int numbelem)
{
	int i;

	i = 0;
	while (i < numbelem)
	{
		ft_putnbr(lstnbr[i]);
		ft_putchar(',');
		i++;
	}
}
