/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_set_pxlfiletoimg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:33:39 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/15 14:42:29 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		set_pxl_if_sprite(t_wind *w, int i, char **lst, void *d)
{
	((t_sprimg *)d)[i].img.ptr_img = mlx_xpm_file_to_image(
	w->mlx, lst[i], &((t_sprimg *)d)[i].img.width, &((t_sprimg *)
	d)[i].img.height);
	((t_sprimg *)d)[i].img.pxl_ptr = mlx_get_data_addr((
	(t_sprimg *)d)[i].img.ptr_img, &((t_sprimg *)d)[i].img.
	bpp, &((t_sprimg *)d)[i].img.size_line, &((t_sprimg *)d)
	[i].img.endian);
}

void		w_set_pxlfiletoimg(t_wind *w, int max, char **lst,
void *d)
{
	int		i;
	int		fd;

	i = 0;
	while (i < max)
	{
		fd = open(lst[i], O_RDONLY);
		if (ft_check_fd(fd, lst[i], 1))
			exit(EXIT_FAILURE);
		else
		{
			if (w->w.isprite)
				set_pxl_if_sprite(w, i, lst, d);
			else
			{
				((t_img *)(d))[i].ptr_img = mlx_xpm_file_to_image(w->mlx,
				lst[i], &((t_img *)(d))[i].width, &((t_img *)(d))[i].height);
				((t_img *)(d))[i].pxl_ptr = mlx_get_data_addr(((t_img *)
				(d))[i].ptr_img, &((t_img *)(d))[i].bpp, &((t_img *)
				(d))[i].size_line, &((t_img *)(d))[i].endian);
			}
		}
		close(fd);
		i++;
	}
}
