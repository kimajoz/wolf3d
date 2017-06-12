/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 13:10:05 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/23 13:10:09 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list			*ft_sort_list(t_list *lst, int (*cmp)(int, int))
{
	t_list		*tmp;
	int			n;
	int			bol;

	bol = 1;
	n = 0;
	while (bol != 0)
	{
		bol = 0;
		tmp = lst;
		while (tmp->next != NULL)
		{
			if ((*cmp)((int)tmp->data, (int)tmp->next->data) == 0)
			{
				n = (int)tmp->data;
				tmp->data = tmp->next->data;
				tmp->next->data = &n;
				bol++;
			}
			tmp = tmp->next;
		}
	}
	return (tmp);
}
