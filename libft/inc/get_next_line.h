/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 18:34:44 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 17:08:01 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../inc/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFF_SIZE 1

int					get_next_line(const int fd, char **line);

typedef struct		s_fd {
	int				fd;
	char			*reste;
	struct s_fd		*next;
}					t_fd;

int					ft_check_fd(int fd, char *filename, int optional);

#endif
