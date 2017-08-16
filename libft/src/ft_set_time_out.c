
#include "../inc/libft.h"

void			ft_set_time_out(t_wind *w, void (*f)(t_wind *w), double endtime)
{
	double		beg;
	double		now;

	beg = ft_get_millitime();
	now = ft_get_millitime();
	/*printf("starttime: %.3f\n", now);
	printf("endtime: %.3f\n", endtime);
	printf("endtime: %.3f\n", beg + endtime);*/
	while (now < (beg + endtime))
	{
		//ft_putchar('-');
		now = ft_get_millitime();
	}
	/*printf("endtime effected: %.3f\n", now);
	ft_putchar('\n');
	ft_putendl("call function");*/
	f(w);
}
