

#include "../inc/libft.h"
#include "../inc/get_next_line.h"

int			ft_check_fd(int fd, char *filename, int needed)
{
	char	*line;

	if (fd == -1 || !get_next_line(fd, &line))
	{
		ft_putstr("File not found or empty file: ");
		ft_putstr(filename);
		if (!needed)
			ft_putstr(" (Optional file)");
		ft_putchar('\n');
		return (1);
	}
	return (0);
}
