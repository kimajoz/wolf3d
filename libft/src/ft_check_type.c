/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:57:16 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/20 16:58:06 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void			ft_check_type(char **lst, int numb, char *type)
{
	int			i;

	i = 0;
	while (i < numb)
	{
		if (ft_strstr(lst[i], type) == 0)
		{
			ft_putstr("Warning !");
			ft_putstr(lst[i]);
			ft_putstr(" file should be of type ");
			ft_putstr(type);
			ft_putendl(" extension.");
		}
		i++;
	}
}

