/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_rotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:49:59 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/19 17:06:54 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		ft_degreetorad(int degrees)
{
	double	radians;
	double	pi;

	pi = 3.1415;
	radians = degrees * (pi / 180);
	return (radians);
}
