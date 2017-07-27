


#include "../inc/libft.h"

void		mlibx_draw_dot(t_wind *w, int x, int y, int color)
{
	char	b;
	char	g;
	char	r;
	int		i;

	if (color == 256 * 256 * 256 + 256 * 256 + 256)
		return ;
	i = (w->img.size_line * y) + (x * (w->img.bpp / 8));
	b = color % 256;
	g = (color / 256) % 256;
	r = (color / 256 / 256) % 256;
	w->img.pxl_ptr[i] = b;
	w->img.pxl_ptr[i + 1] = g;
	w->img.pxl_ptr[i + 2] = r;
}
