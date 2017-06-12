/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 16:58:22 by pbillett          #+#    #+#             */
/*   Updated: 2016/01/05 20:16:50 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strtrim(char const *s)
{
	int		beg;
	int		end;
	int		length;
	char	*str;
	int		i;

	i = 0;
	beg = 0;
	if (!s)
		return (NULL);
	end = ft_strlen(s) - 1;
	while ((s[beg] == ' ' || s[beg] == '\n' || s[beg] == '\t') && s[beg])
		beg++;
	while ((s[end] == ' ' || s[end] == '\n' || s[end] == '\t') && end > 0)
		end--;
	length = end - beg + 1;
	if (s[beg] == '\0')
		return ((char*)s + beg);
	str = ft_strnew(length);
	if (str == NULL)
		return (NULL);
	while (i < length)
		str[i++] = s[beg++];
	return (str);
}
