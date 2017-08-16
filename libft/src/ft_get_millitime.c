#include <time.h>

double		ft_get_millitime(void)
{
	clock_t uptime;

	uptime = clock() / (CLOCKS_PER_SEC / 1000);
	return ((double)uptime);
}
