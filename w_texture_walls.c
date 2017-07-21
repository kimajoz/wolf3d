
#include "wolf3d.h"
#include <stdarg.h> //for ellipsis

int				aff_text_name(t_wind *w, int numargs, ...)
{
	int			i;
	va_list		list; //access ellipsis through va_list

	// https://bobobobo.wordpress.com/2008/01/28/how-to-use-variable-argument-lists-va_list/
	i = 0;
	va_start(list, numargs);
	while (i < numargs)
	{
		char *arg = va_arg(list, char *);
		w->w.lst_text[i] = malloc(sizeof(char) * ft_strlen(arg) + 1);
		ft_strcpy(w->w.lst_text[i], arg);
		i++;
	}
	va_end(list);
	return (0);
}

void			init_texture(t_wind *w)
{
	int			i;

	i = 0;
	w->w.lst_text = malloc(sizeof(char *) * 11);
	aff_text_name(w, 11, "img/greystone.xpm",
						"img/mossy.xpm",
						"img/redbrick.xpm",
						"img/purplestone.xpm",
						"img/wood.xpm",
						"img/colorstone.xpm",
						"img/bluestone.xpm",
						"img/eagle.xpm",
						"img/barrel.xpm",
						"img/greenlight.xpm",
						"img/pillar.xpm");
	w->w.text = malloc(sizeof(void *) * 11);
	w->w.textpxlptr = malloc(sizeof(char *) * 11);
	w->w.bpp = malloc(sizeof(int *) * 11);
	w->w.sline = malloc(sizeof(int *) * 11);
	w->w.endian = malloc(sizeof(int *) * 11);
	while (i < 11)
	{
		w->w.text[i] = mlx_xpm_file_to_image(w->mlx, w->w.lst_text[i], &w->w.textw, &w->w.texth);
		w->w.textpxlptr[i] = mlx_get_data_addr(w->w.text[i], &w->w.bpp[i], &w->w.sline[i], &w->w.endian[i]);
		i++;
	}
}
/*
void			init_screen_texture(t_wind *w)
{
	int			i;
	int			strip_w;
	int			id;
	int			xpm1_x;
	int			xpm1_y;

	i = MMS * MAPLEN;
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
