/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listofnodes_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:38:27 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/19 16:53:22 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minilibx.h"

t_listofnodes				*ft_listofnodes_init(t_listp_path *tmp)
{
	t_listofnodes			*lstnodes;
	t_line					v;
	t_listp_path			*elem;

	lstnodes = malloc(sizeof(t_listofnodes));
	if (!lstnodes)
		return (NULL);
	v.x = tmp->p->x;
	v.y = tmp->p->y;
	v.z = tmp->p->z;
	elem = ft_pathinit(v);
	lstnodes->lstp = elem;
	lstnodes->next = NULL;
	return (lstnodes);
}

t_listofnodes				*ft_listofnodes_add(t_listofnodes *list,
t_listofnodes *elem)
{
	t_listofnodes			*tmp;

	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = elem;
	tmp = tmp->next;
	return (tmp);
}

void						fill_listofnodes(t_wind *w, t_listofnodes *lstnodes)
{
	t_listofnodes			*tmp;
	t_listp_path			*path;
	t_listp_path			*path2;

	tmp = lstnodes;
	while (tmp)
	{
		path = tmp->lstp;
		while (path->next != NULL)
		{
			path2 = path->next;
			w->obj.f.bol = 0;
			w->obj.f.bolfill = 1;
			get_pointinbetween(*path->p, *path2->p, w);
			w->obj.f.bolfill = 0;
			w->obj.f.bol = 1;
			path = path->next;
		}
		tmp = tmp->next;
	}
}

static void					ft_create_node_or_elem(t_listp_path **tmp, int *j,
int *k, t_wind **w)
{
	int						i;
	static t_listofnodes	*lstnodes;

	i = 0;
	if ((*tmp)->p->y == (*w)->obj.f.row_min && (*j) == 0)
	{
		if (i == 0 && (*k) == 0)
		{
			lstnodes = ft_listofnodes_init(*tmp);
			(*w)->obj.f.lstnodesbeg = lstnodes;
			*k = 1;
		}
		else
			lstnodes = ft_listofnodes_add(lstnodes, ft_listofnodes_init(*tmp));
		i++;
		(*j)++;
	}
	else if ((*tmp)->p->y == (*w)->obj.f.row_min && (*j)++ != 0)
	{
		ft_pathadd(lstnodes->lstp,
		ft_pathinit(ft_conv_tpoint_to_tline_coord(*(*tmp)->p)));
	}
}

t_listofnodes				*create_listofnodesperrow_fill(t_wind *w,
t_listp_path *beginlst)
{
	t_listp_path			*tmp;
	int						j;
	int						k;

	k = 0;
	while (w->obj.f.row_min < (w->obj.f.row_max + 1))
	{
		tmp = beginlst;
		j = 0;
		while (tmp)
		{
			ft_create_node_or_elem(&tmp, &j, &k, &w);
			tmp = tmp->next;
		}
		w->obj.f.row_min++;
	}
	return (w->obj.f.lstnodesbeg);
}
