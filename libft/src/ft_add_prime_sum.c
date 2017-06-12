/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_prime_sum.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 19:20:04 by pbillett          #+#    #+#             */
/*   Updated: 2016/10/18 19:23:16 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int			ft_add_prime_sum(int nbr)
{
	int		tot;

	tot = 0;
	while (nbr > 1)
	{
		if (ft_is_prime(nbr) == 1)
			tot += nbr;
		nbr--;
	}
	return (tot);
}
