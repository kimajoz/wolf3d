/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iget_diff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:12:09 by pbillett          #+#    #+#             */
/*   Updated: 2017/10/04 16:13:33 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_iget_diff(int first, int second)
{
	int		i;

	i = 0;
	if (first > second)
		i = first - second;
	else
		i = second - first;
	return (i);
}
