/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browsefile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:37:09 by pbillett          #+#    #+#             */
/*   Updated: 2017/05/15 12:12:45 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "stdio.h" //

t_rt_lsto		*rt_create_obj(int type, char *name, t_dpoint pos, t_dpoint rot, t_rgbcolorf col, int rayon)
{
	t_rt_lsto	*lst;

	lst = malloc(sizeof(t_rt_lsto) * 1);
	lst->data = malloc(sizeof(t_rt_obj) * 1);
	lst->data->type = type;
	lst->data->name = malloc(sizeof(char) * ft_strlen(name) + 1);
	lst->data->name = ft_strcpy(lst->data->name, name);
	lst->data->pos = pos;
	lst->data->rot = rot;
	lst->data->rayon = rayon;
	lst->data->mat = malloc(sizeof(t_rt_material) * 1);
	lst->data->mat->cdiff = col;
	lst->next = NULL;
	return (lst);
}

t_rt_lsto		*rt_create_objlst(t_wind *w)
{
	int			i;
	int			*c;
	int			j;
	t_rt_lsto	*lstfirst;
	t_rt_lsto	*lst;

	i = 0;
	j = 0;
	while (i < w->b.nbr_of_line)
	{
		c = w->b.tab_int[i];
		if (c[0] == 1 || c[0] == 2 || c[0] == 3 || c[0] == 4)
		{
			printf("color.b : %d\n", c[11]);
			lst = rt_create_obj(c[0], w->b.tab_char[i],
								(t_dpoint){c[3], c[4], c[5]},
								(t_dpoint){c[6], c[7], c[8]},
								(t_rgbcolorf){c[9], c[10], c[11]}, c[2]);
			(j++ == 0) ? (lstfirst = lst) : (lstfirst = add_obj_to_list(lstfirst, lst));
		}
		else if (c[0] == 20) // Set position of eyes/cam
		{
			w->rt.e.pos = (t_dpoint){c[3], c[4], c[5]};
			w->rt.e.rot = (t_dpoint){c[6], c[7], c[8]};
		}
		i++;
	}
	return (lstfirst);
}

t_rt_lstl		*rt_create_light(char *name, t_dpoint pos, t_dpoint rot, t_rgbcolorf col)
{
	t_rt_lstl	*lst;

	lst = malloc(sizeof(t_rt_lstl) * 1);
	lst->data = malloc(sizeof(t_rt_el) * 1);
	lst->data->name = malloc(sizeof(char) * ft_strlen(name) + 1);
	lst->data->name = ft_strcpy(lst->data->name, name);
	lst->data->pos = pos;
	lst->data->rot = rot;
	lst->data->color = col;
	lst->next = NULL;
	return (lst);
}

t_rt_lstl		*rt_create_lightlst(t_wind *w)
{
	int			i;
	int			*c;
	int			j;
	t_rt_lstl	*lstfirst;
	t_rt_lstl	*lst;

	i = 0;
	j = 0;
	while (i < w->b.nbr_of_line)
	{
		c = w->b.tab_int[i];
		if (c[0] == 10) // Set position of light
		{
			lst = rt_create_light(w->b.tab_char[i],
								(t_dpoint){c[3], c[4], c[5]},
								(t_dpoint){c[6], c[7], c[8]},
								(t_rgbcolorf){c[9], c[10], c[11]});
			lst->next = NULL;
			if (j++ == 0)
				lstfirst = lst;
			else
				lstfirst = add_objl_to_list(lstfirst, lst);
		}
		i++;
	}
	return (lstfirst);
}

int			**insert_file_to_rt(int fd, int y, t_wind *w)
{
	char	*line;
	char	**tab;
	int		**tab_int;
	int		x;

	tab_int = malloc((y + 1) * sizeof(int *));
	w->b.tab_char = malloc((y + 1) * sizeof(char *));
	w->b.nbr_elem_line = malloc((y + 1) * sizeof(int *));
	y = 0;
	while (get_next_line(fd, &line))
	{
		if (line[0] != '#')
		{
			tab_int[y] = malloc(ft_strlen(line) * sizeof(int));
			tab = ft_strsplit(line, ' ');
			ft_strdel(&line);
			x = 0;
			tab_int[y][x] = ft_atoi(tab[x]);
			ft_strdel(&tab[x]);
			x++;
			w->b.tab_char[y] = malloc((ft_strlen(tab[x]) + 1) * sizeof(char));
			ft_strcpy(w->b.tab_char[y], tab[x]);
			tab_int[y][x] = 0; // We replace text by arbitrary number
			x++;
			while (tab[x])
			{
				tab_int[y][x] = ft_atoi(tab[x]);
				ft_strdel(&tab[x]);
				x++;
			}
			w->b.nbr_elem_line[y] = x;
			free(tab);
			y++;
		}
	}
	w->b.nbr_of_line = y;
	return (tab_int);
}

int			**rt_file(char *filename, int y, t_wind *w)
{
	int		fd;
	int		fd1;
	char	*line;
	int		**tab_int;

	fd = open(filename, O_RDONLY);
	fd1 = open(filename, O_RDONLY);
	if (check_fd(fd1) == 1)
		return (NULL);
	y = 0;
	while (get_next_line(fd1, &line))
	{
		ft_strdel(&line);
		y++;
	}
	w->b.nbrtot_of_line = y;
	if (ft_check_parsing(filename) == 1)
		return (0);
	tab_int = insert_file_to_rt(fd, y, w);
	close(fd1);
	close(fd);
	return (tab_int);
}
