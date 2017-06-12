

#include "../inc/libft.h"
#include "../inc/get_next_line.h"

int			check_fd(int fd)
{
	char	*line;

	if (fd == -1 || !get_next_line(fd, &line))
	{
		ft_putstr("empy file, please check source_file\n");
		return (1);
	}
	return (0);
}
