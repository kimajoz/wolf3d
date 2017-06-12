/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pythagore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 12:50:30 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/23 13:09:44 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

float		ft_pythagore(float a, float b)
{
	float	c;

	c = sqrt(ft_squared(a) + ft_squared(b));
	return (c);
}
