/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listofnodes_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:38:27 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/19 16:45:49 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minilibx.h"

void				ft_listofnodes_free(t_listofnodes *lstnodes)
{
	t_listofnodes	*tmp;
	t_listofnodes	*prev;
	t_listp_path	*path;
	t_listp_path	*prevpath;

	tmp = lstnodes;
	while (tmp)
	{
		prev = tmp;
		path = tmp->lstp;
		while (path)
		{
			prevpath = path;
			path = path->next;
			free(prevpath->p);
			free(prevpath);
		}
		tmp = tmp->next;
		free(prev);
	}
}
