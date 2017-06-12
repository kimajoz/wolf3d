/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 17:55:48 by pbillett          #+#    #+#             */
/*   Updated: 2016/01/13 17:17:34 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdlib.h>

char		*ft_strdup(const char *s1)
{
	char	*str;
	int		length;

	length = ft_strlen(s1) + 1;
	str = (char*)malloc(length * sizeof(*str));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, (char*)s1);
	str[ft_strlen((char*)s1)] = '\0';
	return (str);
}
