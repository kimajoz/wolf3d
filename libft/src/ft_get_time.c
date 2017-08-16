#include <time.h>

double		ft_get_time(void)
{
	time_t rawtime;

	time ( &rawtime );
	return ((double)rawtime);
}
