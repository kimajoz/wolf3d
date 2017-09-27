/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_sound_duration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 17:52:49 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/27 18:14:29 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdlib.h>
#include <stdio.h>

double		ft_get_sound_duration(char *filename, int os)
{
	char	*cmd;
	char	*cmd2;
	double	res;

	if (os == 0) // Linux
	{
		cmd = ft_strjoin("ainfo ", filename);
		cmd2 = ft_strjoin(cmd, " | awk '/ estimated duration/ { print $3 }'");
	}
	else if (os == 1) // Macos
	{
		cmd = ft_strjoin("afinfo ", filename);
		cmd2 = ft_strjoin(cmd, " | awk '/ estimated duration/ { print $3 }'");
	}
	else
	{
		cmd = ft_strjoin("afinfo ", filename);
		cmd2 = ft_strjoin(cmd, " | awk '/ estimated duration/ { print $3 }'");
	}
	res = system(cmd2);
	printf("sound duration: %.3f\n", res);
	free(cmd);
	free(cmd2);
	return (res);
}
