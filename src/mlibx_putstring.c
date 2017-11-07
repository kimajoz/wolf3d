/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlibx_putstring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:36:27 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/02 15:36:29 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	mlibx_putstring(char *s, int l, int c, t_wind *w)
{
	mlx_string_put(w->mlx, w->win, 3 + c * 10, l * 20, 0xFFFFFF, s);
}
