/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_texture_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 15:26:08 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/14 19:53:20 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"
#include <stdarg.h>

static int				aff_text_name(char **lst_text, int numargs, ...)
{
	int			i;
	va_list		list;
	char		*arg;

	i = 0;
	va_start(list, numargs);
	while (i < numargs)
	{
		arg = va_arg(list, char *);
		if (!(lst_text[i] = malloc(sizeof(char) * ft_strlen(arg) + 1)))
			exit(0);
		ft_strcpy(lst_text[i], arg);
		i++;
	}
	va_end(list);
	return (0);
}

static int				aff_block(t_sprimg *block, int numargs, ...)
{
	int			i;
	va_list		list;
	int			arg;

	i = 0;
	ft_comment("aff_block 01");
	va_start(list, numargs);
	ft_comment("aff_block 02");
	while (i < numargs)
	{
		ft_comment("aff_block 03");
		arg = va_arg(list, int);
		block[i].block = arg;
		i++;
	}
		ft_comment("aff_block 04");
	va_end(list);
		ft_comment("aff_block 05");
	return (0);
}

void					init_sprites(t_wind *w)
{
	w->w.sprnb = 7;
	ft_comment("init_sprites 01");
	if (!(w->w.lst_sprite = malloc(sizeof(char *) * w->w.sprnb)))
		exit(1);
	ft_comment("init_sprites 02");
	aff_text_name(w->w.lst_sprite, w->w.sprnb,
						"img/sprites/table-chairs.xpm",
						"img/sprites/armor.xpm",
						"img/sprites/plant-green.xpm",
						"img/sprites/lamp.xpm",
						"img/sprites/lustre.xpm",
						"img/sprites/pillar.xpm",
						"img/sprites/guard.xpm");
	ft_comment("init_sprites 03");
	ft_check_type(w->w.lst_sprite, w->w.sprnb, "xpm");
	ft_comment("init_sprites 04");
	if (!(w->w.sprite = malloc(sizeof(t_sprimg) * w->w.sprnb)))
		exit(1);
	ft_comment("init_sprites 05");
	w->w.isprite = 1;
	w->w.sprite[0].img.x = 3;
	ft_comment("init_sprites 05a");
	w_set_pxlfiletoimg(w, w->w.sprnb, w->w.lst_sprite, w->w.sprite);
	ft_comment("init_sprites 05");
	w->w.isprite = 0;
	aff_block(w->w.sprite, w->w.sprnb, 1, 1, 1, 0, 0, 1, 1);
	ft_comment("init_sprites 06");
}

void					init_texture(t_wind *w)
{
	int			nbtext;

	nbtext = 11;
	if (!(w->w.lst_text = malloc(sizeof(char *) * nbtext)))
		exit(0);
	aff_text_name(w->w.lst_text, nbtext, "img/walls/greystone.xpm",
						"img/walls/mossy.xpm",
						"img/walls/redbrick.xpm",
						"img/walls/purplestone.xpm",
						"img/walls/wood.xpm",
						"img/walls/colorstone.xpm",
						"img/walls/bluestone.xpm",
						"img/walls/eagle.xpm",
						"img/walls/blue_brick_hi.xpm",
						"img/walls/doorm.xpm",
						"img/walls/wall_red_door.xpm");
	ft_check_type(w->w.lst_text, nbtext, "xpm");
	if (!(w->w.text = malloc(sizeof(t_img) * nbtext)))
		exit(0);
	ft_comment("init_texture 01");
	w_set_pxlfiletoimg(w, nbtext, w->w.lst_text, w->w.text);
	ft_comment("init_texture 02");
}

void					init_guns(t_wind *w)
{
	int			nbtext;

	nbtext = 1;
	if (!(w->w.lst_weapon = malloc(sizeof(char *) * nbtext)))
		exit(0);
	aff_text_name(w->w.lst_weapon, nbtext, "img/guns/guns.xpm");
	ft_check_type(w->w.lst_weapon, nbtext, "xpm");
	if (!(w->w.weapon = malloc(sizeof(t_img) * nbtext)))
		exit(0);
	ft_comment("init_guns");
	w_set_pxlfiletoimg(w, nbtext, w->w.lst_weapon, w->w.weapon);
	ft_comment("init_guns b");
}
