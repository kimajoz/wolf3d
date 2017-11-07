/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_clear_vis_sprites.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:05:42 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 20:48:00 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		w_clear_vis_sprites2dspr_list(t_wind *w)
{
	int		i;

	i = 0;
	if (w->w.oldvisiblespr)
	{
		free(w->w.oldvisiblespr);
		w->w.oldvisiblespr = NULL;
	}
	if (!(w->w.oldvisiblespr = malloc(w->w.nbtotsprprog * sizeof(t_sprite))))
		exit(0);
	i = 0;
	while (i < w->w.sprnbvis)
	{
		w->w.oldvisiblespr[i] = w->w.visiblespr[i];
		w->w.oldvisiblespr[i].vis = 0;
		i++;
	}
	w->w.sprnbvis = 0;
	free(w->w.visiblespr);
	w->w.visiblespr = NULL;
	if (!(w->w.visiblespr = malloc(w->w.nbtotsprprog * sizeof(t_sprite))))
		exit(0);
}

void		w_clear_vis_sprites(t_wind *w)
{
	int		y;
	int		x;

	y = 0;
	while (y < w->b.nbrtot_of_line)
	{
		x = 0;
		while (x < w->b.nbr_elem_line[3])
			w->w.tab_int_spr[y][x++].vis = 0;
		y++;
	}
	w_clear_vis_sprites2dspr_list(w);
}
