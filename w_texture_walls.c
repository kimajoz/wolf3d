
#include "wolf3d.h"

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
}
