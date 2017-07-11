
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

static float	get_diff(float i, float j)
{
	float		res;

	res = (i > j) ? (i - j) : (j - i);
	return (res);
}

t_line		mlibx_set_parameters_tline(t_line v)
{
	v.midx = v.xdest + ((rint(v.x) - v.xdest) / 2);
	v.midy = v.ydest + ((rint(v.y) - v.ydest) / 2);
	v.sign_x = get_sign((int)v.x, (int)v.xdest);
	v.sign_y = get_sign((int)v.y, (int)v.ydest);
	v.diff_x = get_diff(v.x, v.xdest);
	v.diff_y = get_diff(v.y, v.ydest);
	v.bigdiff = (v.diff_x > v.diff_y) ? v.diff_x : v.diff_y;
	return (v);
}

void		mlibx_draw_pixel_line_float(t_dpoint point, t_dpoint pointd, t_wind *w, char *color)
{
	t_line	v;

	v.x = point.x;
	v.y = point.y;
	v.xdest = pointd.x;
	v.ydest = pointd.y;
	ft_putendl("before set parameters tline");
	v = mlibx_set_parameters_tline(v);
	ft_putendl("set parameters tline ok");
	ft_putstr("while");
	while (rint(v.x) != rint(v.xdest) || rint(v.y) != rint(v.ydest))
	{
		ft_putchar('.');
		if (v.x != v.xdest)
			v.x += (v.sign_x * (v.diff_x / v.bigdiff));
		if (v.y != v.ydest)
			v.y += (v.sign_y * (v.diff_y / v.bigdiff));
		if (mlibx_dot_in_window(w, rint(v.x), rint(v.y)))
			mlibx_draw_pixel(w, rint(v.x), rint(v.y), color);
	}
	ft_putstr("end");
	ft_putchar('\n');
}
