/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time_clean.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:43:56 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 16:46:09 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

char		*ft_get_time_clean(void)
{
	time_t rawtime;

	time(&rawtime);
	return (ctime(&rawtime));
}
