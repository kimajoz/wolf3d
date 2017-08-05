#include "../inc/libft.h"

double		ft_rot_fabs(double n)
{
	if (n >= 360)
		n -= 360;
	else if (n < 0)
		n += 360;
	return (n);
}
