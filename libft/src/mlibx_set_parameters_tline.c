/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_parameters_tline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:10:43 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/10 15:15:08 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_line		ft_conv_tpoint_to_tline_coord(t_point p)
{
	t_line	t;

	t.x = p.x;
	t.y = p.y;
	t.z = p.z;
	return (t);
}
