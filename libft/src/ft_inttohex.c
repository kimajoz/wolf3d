/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgbtohexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:04:05 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/04 12:17:20 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char			*ft_inttohex(int n)
{
	char		*hex;
	int			i;
	int			dizaine;

	hex = ft_strnew(4);
	i = 0;
	hex[i++] = '0';
	hex[i++] = 'x';
	dizaine = n / 16;
	if (dizaine < 10)
		hex[i++] = dizaine + '0';
	else
		hex[i++] = dizaine % 10 + 'A';
	n = n - (dizaine * 16);
	if (n < 10)
		hex[i++] = n + '0';
	else
		hex[i++] = n % 10 + 'A';
	return (hex);
}
