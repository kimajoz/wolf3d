
#include <sys/stat.h>

int					ft_does_file_exist(const char *filename)
{
	struct stat		st;
	int				result;

	result = stat(filename, &st);
	return(result == 0);
}
