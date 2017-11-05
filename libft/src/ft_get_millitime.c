/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_millitime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:43:11 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 16:43:13 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

double		ft_get_millitime(void)
{
	clock_t uptime;

	uptime = clock() / (CLOCKS_PER_SEC / 1000);
	return ((double)uptime);
}
