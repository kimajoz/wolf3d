/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgbtohexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:04:05 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/19 17:16:52 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char		*ft_mini_sub_hexajoin(char *hexcolor, int begin_numb)
{
	char		*hexpart;
	char		*begin;
	char		*result;

	begin = ft_strnew(2);
	begin = ft_strcpy(begin, "0x");
	hexpart = ft_strsub(hexcolor, begin_numb, 2);
	result = ft_strjoin(begin, hexpart);
	ft_strdel(&hexpart);
	ft_strdel(&begin);
	return (result);
}

t_rgbcolor		ft_hexatorgb(char *hexcolor)
{
	t_rgbcolor	rgbcolor;
	char		*r;
	char		*g;
	char		*b;

	b = ft_mini_sub_hexajoin(hexcolor, 2);
	g = ft_mini_sub_hexajoin(hexcolor, 4);
	r = ft_mini_sub_hexajoin(hexcolor, 6);
	rgbcolor.r = ft_hextoint(r);
	rgbcolor.g = ft_hextoint(g);
	rgbcolor.b = ft_hextoint(b);
	ft_strdel(&r);
	ft_strdel(&g);
	ft_strdel(&b);
	return (rgbcolor);
}
