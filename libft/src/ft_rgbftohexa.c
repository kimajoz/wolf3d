/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgbtohexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:04:05 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/19 17:15:30 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char			*ft_rgbftohexa(t_rgbcolorf rgbcolorf)
{
	t_rgbcolor	color;
	char		*res;

	color.r = (int)rgbcolorf.r;
	color.g = (int)rgbcolorf.g;
	color.b = (int)rgbcolorf.b;
	res = ft_rgbtohexa(color);
	return (res);
}
