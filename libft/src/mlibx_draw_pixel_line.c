
#include "../inc/libft.h"

static int	get_sign(int first, int second)
{
	int		sign;

	if (first > second)
		sign = -1;
	else if (first == second)
		sign = 0;
	else
		sign = 1;
	return (sign);
}

static int	get_diff(int first, int second)
{
	int		i;

	i = 0;
	if (first > second)
		i = first - second;
	else
		i = second - first;
	return (i);
}

t_line		mlibx_set_parameters_tline(t_line v)
{
	v.midx = v.xdest + ((rint(v.x) - v.xdest) / 2);
	v.midy = v.ydest + ((rint(v.y) - v.ydest) / 2);
	v.sign_x = get_sign(v.x, v.xdest);
	v.sign_y = get_sign(v.y, v.ydest);
	v.diff_x = get_diff(v.x, v.xdest);
	v.diff_y = get_diff(v.y, v.ydest);
	if (v.diff_x > v.diff_y)
		v.bigdiff = v.diff_x;
	else if (v.diff_y > v.diff_x)
		v.bigdiff = v.diff_y;
	else
		v.bigdiff = v.diff_y;
	return (v);
}

void		mlibx_draw_pixel_line(t_point point, t_point pointd, t_wind *w, char *color)
{
	t_line	v;

	v.x = point.x;
	v.y = point.y;
	v.xdest = pointd.x;
	v.ydest = pointd.y;
	v = mlibx_set_parameters_tline(v);
	while (rint(v.x) != v.xdest || rint(v.y) != v.ydest)
	{
		if (v.x != v.xdest)
			v.x += (v.sign_x * (v.diff_x / v.bigdiff));
		if (v.y != v.ydest)
			v.y += (v.sign_y * (v.diff_y / v.bigdiff));
		if (mlibx_dot_in_window(w, rint(v.x), rint(v.y)))
			mlibx_draw_pixel(w, rint(v.x), rint(v.y), color);
	}
}

void		mlibx_draw_pixel_line_int(t_point point, t_point pointd, t_wind *w, int color)
{
	t_line	v;

	v.x = point.x;
	v.y = point.y;
	v.xdest = pointd.x;
	v.ydest = pointd.y;
	v = mlibx_set_parameters_tline(v);
	while (rint(v.x) != v.xdest || rint(v.y) != v.ydest)
	{
		if (v.x != v.xdest)
			v.x += (v.sign_x * (v.diff_x / v.bigdiff));
		if (v.y != v.ydest)
			v.y += (v.sign_y * (v.diff_y / v.bigdiff));
		if (mlibx_dot_in_window(w, rint(v.x), rint(v.y)))
			mlibx_draw_dot(w, rint(v.x), rint(v.y), color);
	}
}
