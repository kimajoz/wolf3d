/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_check_progstart.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 19:30:14 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/14 20:16:09 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

char			*new_file_name(char *oldfilename, char *ext)
{
	char		*str;
	char		*strsub;
	int			len;

	len = ft_strlen(ext);
	str = ft_strnew(ft_strlen(oldfilename));
	strsub = ft_strsub(oldfilename, 0, ft_strlen(oldfilename) - len);
	ft_strcpy(str, strsub);
	ft_strdel(&strsub);
	ft_strcat(str, ext);
	return (str);
}

int				w_check_progstart(t_wind *w, char *filename)
{
	char		*fsprites;
	char		*fparam;

	w->width = 800;
	w->height = 600;
	if (!ft_strrstr(filename, ".scn"))
	{
		ft_putendl("File wrong type: Needed .scn input file extension.");
		return (0);
	}
	w = create_new_window(w, "Wolf3d", w->width, w->height);
	w_file(filename, w, 1);
	fsprites = new_file_name(filename, ".spr");
	fparam = new_file_name(filename, ".par");
	w_file(fsprites, w, 0);
	w_file(fparam, w, 0);
	ft_strdel(&fsprites);
	free(fsprites);
	ft_strdel(&fparam);
	free(fparam);
	return (1);
}
