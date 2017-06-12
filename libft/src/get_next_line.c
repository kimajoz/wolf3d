/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 18:39:44 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/19 13:18:12 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

static t_fd			*add_list(int fd)
{
	t_fd		*list;

	list = (t_fd *)malloc(sizeof(t_fd));
	if (list == NULL)
		return (NULL);
	list->fd = fd;
	list->reste = NULL;
	list->next = NULL;
	return (list);
}

static t_fd			*init_list(int fd, t_fd **list)
{
	t_fd			*tmp;

	if (*list == NULL)
	{
		*list = add_list(fd);
		tmp = *list;
		tmp->next = NULL;
	}
	else
	{
		tmp = *list;
		while (tmp->next != NULL && tmp->fd != fd)
			tmp = tmp->next;
		if (tmp->fd != fd && tmp->next == NULL)
		{
			tmp->next = add_list(fd);
			tmp = tmp->next;
		}
	}
	return (tmp);
}

static int			ft_join(char **reste, char **buff, int *ret)
{
	char			*new;

	new = NULL;
	if (*ret < 0)
		return (-1);
	(*buff)[*ret] = '\0';
	if (*reste == NULL)
		new = ft_strdup(*buff);
	else
	{
		new = ft_strjoin(*reste, *buff);
		ft_strdel(reste);
	}
	*reste = new;
	return (0);
}

static void			new_linefound(int *ret, char ***line, char **r, char *endlr)
{
	char			*tes;

	*ret = 1;
	**line = ft_strsub(*r, 0, endlr - *r);
	if (**line == NULL)
		return ;
	tes = ft_strsub(*r, endlr - *r + 1, ft_strlen(endlr));
	if (tes == NULL)
		return ;
	ft_strcpy(*r, tes);
	ft_strdel(&tes);
}

int					get_next_line(const int fd, char **line)
{
	char			*buff;
	int				ret;
	static	t_fd	*list;
	t_fd			*tmp;

	ret = 0;
	if (BUFF_SIZE <= 0 || !line || !(tmp = init_list(fd, &list))
			|| !(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	while (tmp->reste == NULL || (!(ft_strchr(tmp->reste, '\n'))
	&& (ret = read(fd, buff, BUFF_SIZE))))
	{
		if (ft_join(&tmp->reste, &buff, &ret) == -1)
			return (-1);
	}
	ft_strdel(&buff);
	if (tmp->reste && ft_strchr(tmp->reste, '\n'))
		new_linefound(&ret, &line, &tmp->reste, ft_strchr(tmp->reste, '\n'));
	else if (!ft_strchr(tmp->reste, '\n') && ft_strlen(tmp->reste))
	{
		*line = ft_strdup(tmp->reste);
		ft_strdel(&(tmp->reste));
		return ((ret == 0) ? 1 : 0);
	}
	return (ret > 0 || ft_strlen(tmp->reste));
}
