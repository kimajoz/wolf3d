/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:59:09 by pbillett          #+#    #+#             */
/*   Updated: 2016/01/05 19:56:48 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char *str;

	str = (char *)malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, size);
	return (str);
}
