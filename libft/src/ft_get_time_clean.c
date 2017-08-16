
#include <time.h>

char		*ft_get_time_clean(void)
{
	time_t rawtime;

	time ( &rawtime );
	return (ctime(&rawtime));
}
