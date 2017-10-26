
#include "../inc/libft.h"

void			ft_set_time_out(t_wind *w, void (*f)(t_wind *w), double endtime)
{
	double		beg;
	double		now;

	beg = ft_get_millitime();
	now = ft_get_millitime();
	while (now < (beg + endtime))
		now = ft_get_millitime();
	f(w);
}
