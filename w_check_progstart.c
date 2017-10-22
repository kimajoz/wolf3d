/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_check_progstart.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 19:30:14 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/04 20:12:37 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char			*new_file_name(char *oldfilename, char *ext)
{
	char		*str;
	char		*strsub;
	int			len;

	len = ft_strlen(ext);
	str = ft_strnew(ft_strlen(oldfilename));
	strsub = ft_strsub(oldfilename, 0, ft_strlen(oldfilename) - len);
	ft_strcpy(str, strsub);
	free(strsub);
	ft_strcat(str, ext);
	//free(ext);
	return (str);
}

int				w_check_progstart(t_wind *w, char *filename)
{
	char		*fsprites;
	char		*fparam;

	w->width = 800;
	w->height = 600;
	if (!ft_strstr(filename, "scn"))
	{
		ft_putendl("File wrong type: Needed .scn input file extension.");
		return (0);
	}
	*w = create_new_window("Wolf3d", w->width, w->height);
	ft_putendl("before rt_file simple");
	rt_file(filename, w, 1);
	ft_putendl("after rt_file simple");
	fsprites = new_file_name(filename, ".spr");
	fparam = new_file_name(filename, ".par");
	ft_putendl("before rt_file fsprites");
	rt_file(fsprites, w, 0);
	ft_putendl("after rt_file fsprites");
	rt_file(fparam, w, 1);
	ft_putendl("after rt_file param");
	return (1);
}
