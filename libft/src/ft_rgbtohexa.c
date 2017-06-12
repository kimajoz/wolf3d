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

char			*ft_rgbtohexa(t_rgbcolor rgbcolor)
{
	char		*hexa_color;
	int			i;
	char		*r;
	char		*g;
	char		*b;

	i = 0;
	hexa_color = ft_strnew(9);
	r = ft_inttohex(rgbcolor.r);
	g = ft_inttohex(rgbcolor.g);
	b = ft_inttohex(rgbcolor.b);
	hexa_color[i++] = '0';
	hexa_color[i++] = 'x';
	hexa_color[i++] = r[2];
	hexa_color[i++] = r[3];
	hexa_color[i++] = g[2];
	hexa_color[i++] = g[3];
	hexa_color[i++] = b[2];
	hexa_color[i++] = b[3];
	ft_strdel(&r);
	ft_strdel(&g);
	ft_strdel(&b);
	return (hexa_color);
}
