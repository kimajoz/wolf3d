/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 20:52:51 by pbillett          #+#    #+#             */
/*   Updated: 2016/01/13 17:16:24 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdlib.h>

void		ft_lstdel(t_list **alst, void (*del) (void *, size_t))
{
	t_list	*tmp;
	t_list	*new;

	tmp = *alst;
	while (tmp)
	{
		new = tmp->next;
		del(tmp->data, tmp->data_size);
		free(tmp);
		tmp = new;
	}
	*alst = NULL;
}
