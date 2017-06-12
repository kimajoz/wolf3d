/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_listofnodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:11:14 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/19 16:56:37 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minilibx.h"

static int				croissant(int a, int b)
{
	return (a <= b);
}

t_listp_path			*ft_sort_listp(t_listp_path *lst, int (*cmp)(int, int))
{
	t_listp_path		*tmp;
	t_sortlistp			s;
	int					bol;

	bol = 1;
	while (bol != 0)
	{
		bol = 0;
		tmp = lst;
		while (tmp->next != NULL)
		{
			if ((*cmp)((int)tmp->p->x, (int)tmp->next->p->x) == 0)
			{
				s.mem_x = (int)tmp->p->x;
				s.mem_z = (int)tmp->p->z;
				tmp->p->x = tmp->next->p->x;
				tmp->p->z = tmp->next->p->z;
				tmp->next->p->x = s.mem_x;
				tmp->next->p->z = s.mem_z;
				bol++;
			}
			tmp = tmp->next;
		}
	}
	return (lst);
}

void					sort_listofnodes(t_listofnodes *lstnodes)
{
	t_listofnodes		*tmp;

	tmp = lstnodes;
	while (tmp)
	{
		tmp->lstp = ft_sort_listp(tmp->lstp, croissant);
		tmp = tmp->next;
	}
}
