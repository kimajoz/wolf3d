
#include "wolf3d.h"
#include <stdarg.h> //for ellipsis

int				aff_text_name(char **lst_text, int numargs, ...)
{
	int			i;
	va_list		list; //access ellipsis through va_list

	// https://bobobobo.wordpress.com/2008/01/28/how-to-use-variable-argument-lists-va_list/
	i = 0;
	va_start(list, numargs);
	while (i < numargs)
	{
		char *arg = va_arg(list, char *);
		lst_text[i] = malloc(sizeof(char) * ft_strlen(arg) + 1);
		ft_strcpy(lst_text[i], arg);
		i++;
	}
	va_end(list);
	return (0);
}

int				aff_block(t_sprimg *block, int numargs, ...)
{
	int			i;
	va_list		list; //access ellipsis through va_list

	// https://bobobobo.wordpress.com/2008/01/28/how-to-use-variable-argument-lists-va_list/
	i = 0;
	va_start(list, numargs);
	while (i < numargs)
	{
		int arg = va_arg(list, int);
		//block[i] = malloc(sizeof(char) * ft_strlen(arg) + 1);
		//ft_strcpy(lst_text[i], arg);
		block[i].block = arg;
		i++;
	}
	va_end(list);
	return (0);
}

void			check_type_xpm(char **lst, int numb)
{
	int			i;

	i = 0;
	while (i < numb)
	{
		if (ft_strstr(lst[i], "xpm") == 0)
		{
			ft_putstr("Warning !");
			ft_putstr(lst[i]);
			ft_putendl(" file should be of xpm extension.");
		}
		i++;
	}
}

void			init_sprites(t_wind *w)
{
	int			i;
	int			fd;

	i = 0;
	w->w.sprnb = 5;
	w->w.lst_sprite = malloc(sizeof(char *) * w->w.sprnb);
	aff_text_name(w->w.lst_sprite, w->w.sprnb,
						"img/sprites/table-chairs.xpm",
						"img/sprites/armor.xpm",
						"img/sprites/plant-green.xpm",
						"img/sprites/lamp.xpm",
						"img/sprites/lustre.xpm",
						"img/sprites/pillar.xpm",
						"img/sprites/guard.xpm");
	check_type_xpm(w->w.lst_sprite, w->w.sprnb);
	w->w.sprite = malloc(sizeof(t_sprimg) * w->w.sprnb);
	while (i < w->w.sprnb)
	{
		fd = open(w->w.lst_sprite[i], O_RDONLY);
		if (ft_check_fd(fd, w->w.lst_sprite[i], 1) == 0)
		{
			w->w.sprite[i].img.ptr_img = mlx_xpm_file_to_image(w->mlx, w->w.lst_sprite[i], &(w->w.sprite[i].img.width), &(w->w.sprite[i].img.height));
			w->w.sprite[i].img.pxl_ptr = mlx_get_data_addr(w->w.sprite[i].img.ptr_img, &w->w.sprite[i].img.bpp, &w->w.sprite[i].img.size_line, &w->w.sprite[i].img.endian);
		}
		else
			exit(EXIT_FAILURE);
		//printf("bpp: %d\n", w->w.sprite[i].bpp);
		i++;
	}
	aff_block(w->w.sprite, w->w.sprnb, 1, 1, 1, 0, 1);
}

void			init_texture(t_wind *w)
{
	int			i;
	int			fd;
	int			nbtext;

	i = 0;
	nbtext = 10;
	w->w.lst_text = malloc(sizeof(char *) * nbtext);
	aff_text_name(w->w.lst_text, nbtext, "img/greystone.xpm",
						"img/mossy.xpm",
						"img/redbrick.xpm",
						"img/purplestone.xpm",
						"img/wood.xpm",
						"img/colorstone.xpm",
						"img/bluestone.xpm",
						"img/eagle.xpm",
						"img/blue_brick_hi.xpm",
						"img/wall_red_door.xpm");
	check_type_xpm(w->w.lst_text, nbtext);
	w->w.text = malloc(sizeof(t_img) * nbtext);
	while (i < nbtext)
	{
		fd = open(w->w.lst_text[i], O_RDONLY);
		if (ft_check_fd(fd, w->w.lst_text[i], 1) == 0)
		{
			w->w.text[i].ptr_img = mlx_xpm_file_to_image(w->mlx, w->w.lst_text[i], &(w->w.text[i].width), &(w->w.text[i].height));
			w->w.text[i].pxl_ptr = mlx_get_data_addr(w->w.text[i].ptr_img, &w->w.text[i].bpp, &w->w.text[i].size_line, &w->w.text[i].endian);
		}
		else
			exit(EXIT_FAILURE);
		i++;
	}
}

/*
void			draw_texture(t_wind *w, int n)
{
	int			y;
	int			x;
	//t_rgbcolor	col;
	//char		*hexcol;
	int			*res;

	x = 0;
	y = 0;
	while (x < w->w.textw)
	{
		while (y < w->w.texth)
		{
			res = (w->w.text[n] + (y * w->w.sline[n]) + (x * (w->w.bpp[n])));
			//col.g = (int)(w->w.text[n] + (y * w->w.sline[n]) + (x * (w->w.bpp[n])) + 1);
			//col.b = (int)(w->w.text[n] + (y * w->w.sline[n]) + (x * (w->w.bpp[n])) + 2);
			printf("res:%i\n", *res);
			//hexcol = ft_rgbtohexa(col);
			//mlibx_draw_pixel(w, x, y, hexcol);
			y++;
		}
		x++;
	}

}*/


/*
void			init_screen_texture(t_wind *w)
{
	int			i;
	int			strip_w;
	int			id;
	int			xpm1_x;
	int			xpm1_y;

	i = w->w.marginw;
	id = 0;
	strip_w = 2;
	w->w.sstrip = malloc(sizeof(void **) * w->width);
	while (i < w->width)
	{
		w->w.sstrip[id] = malloc(sizeof(void *));
		w->w.sstrip[id] = mlx_xpm_file_to_image(w->mlx,"img/walls.xpm",&xpm1_x,&xpm1_y);
		mlx_put_image_to_window(w->mlx, w->win, w->w.sstrip[id], i, 0);
		i += strip_w;
		id++;
	}
}*/
/*
void			w_texture_walls(t_wind *w)
{
	void		*im2;
	int			xpm1_x;
	int			xpm1_y;
	//char		*data2;
	//int			endian2;
	//int			sl2;

	//printf(" => Xpm from file ...");
	//if (!(im2 = mlx_xpm_file_to_image(w->mlx,"open.xpm",&xpm1_x,&xpm1_y)))
	if (!(im2 = mlx_xpm_file_to_image(w->mlx,"img/walls.xpm",&xpm1_x,&xpm1_y)))
	{
	  printf(" !! KO !!\n");
	  exit(1);
	}
	//w->img.ptr_img
	//w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel, &w->img.size_line, &w->img.endian_type);
	//mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel, &sl2, &endian2);
	//printf("OK (xpm %dx%d)(img bpp2: %d, sizeline2: %d endian: %d)\n",
	//xpm1_x, xpm1_y, w->img.bits_per_pixel, sl2, endian2);

	//printf(" => Put xpm ...");
	//mlx_put_image_to_window(w->mlx, w->win, im2, 0, 0);
	mlx_put_image_to_window(w->mlx, w->win, im2, 100, 100);
	//printf("OK\n");
	//sleep(2);
}*/
