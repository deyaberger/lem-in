/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_result.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:17:03 by dberger           #+#    #+#             */
/*   Updated: 2019/11/02 20:09:30 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void	ft_result(char *str, t_info info, t_ways *best)
{
	int i;
	int j;
	int a;
	int nb;
	t_room *room;

	i = 0;
	j = 0;
	a = 1;
	room = info.start;
	nb = info.ant_nb;
	ft_printf("%s\n", str);	
	free(str);
//	while (nb > 0);
//	{
		while (i < best->nb_ways)
		{
			room = best->steps[i][j];
			room->ant_index = a;
			ft_printf("L%d-%s", a, room->name);
			if (i < best->nb_ways - 1)
				ft_printf(" ");
			i++;
			a++;
		}
//	}
	(void)info;
	(void)best;
}
