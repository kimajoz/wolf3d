/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 20:13:37 by pbillett          #+#    #+#             */
/*   Updated: 2016/01/13 17:14:45 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdlib.h>

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	if (content == NULL)
	{
		list->data = NULL;
		list->data_size = 0;
	}
	else
	{
		list->data = malloc(content_size);
		if (!(list->data))
			return (NULL);
		list->data = ft_memcpy(list->data, content, content_size);
		list->data_size = content_size;
	}
	list->next = NULL;
	return (list);
}
