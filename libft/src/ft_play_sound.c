/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_play_sound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:09:13 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/05 16:38:04 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdlib.h>

int			ft_play_sound(char *filename, int os)
{
	char	*cmd;

	if (os == 0)
		cmd = ft_strjoin("aplay ", filename);
	else if (os == 1)
		cmd = ft_strjoin("afplay ", filename);
	else
		cmd = ft_strjoin("aplay ", filename);
	system(cmd);
	free(cmd);
	return (0);
}
