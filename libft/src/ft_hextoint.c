/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgbtohexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:04:05 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/19 17:17:20 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx.h"

int				ft_hextoint(char *s)
{
	int			i;
	int			numb;
	int			tot;

	i = 0;
	if ((s[i] == '0') && (s[i + 1] == 'X' || s[i + 1] == 'x'))
		i += 2;
	numb = 0;
	tot = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			numb = s[i] - '0';
		else if (s[i] >= 'a' && s[i] <= 'f')
			numb = s[i] - 'a' + 10;
		else if (s[i] >= 'A' && s[i] <= 'F')
			numb = s[i] - 'A' + 10;
		else
			ft_putstr("error color hexa\n");
		tot = 16 * tot + numb;
		i++;
	}
	return (tot);
}
