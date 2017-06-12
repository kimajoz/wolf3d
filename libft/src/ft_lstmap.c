/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 14:29:27 by pbillett          #+#    #+#             */
/*   Updated: 2016/01/09 20:54:09 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *result;
	t_list *newlist;
	t_list *tmp;

	if (!lst || !f)
		return (NULL);
	newlist = (f)(lst);
	result = ft_lstnew(newlist->data, newlist->data_size);
	if (result != NULL)
	{
		tmp = result;
		lst = lst->next;
		while (lst)
		{
			newlist = (f)(lst);
			if (newlist == NULL)
				return (NULL);
			tmp->next = ft_lstnew(newlist->data, newlist->data_size);
			tmp = tmp->next;
			lst = lst->next;
		}
	}
	return (result);
}
