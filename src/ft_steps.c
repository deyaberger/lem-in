/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:36:09 by dberger           #+#    #+#             */
/*   Updated: 2019/10/28 16:09:10 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

BOOL	ft_steps(t_info *info, t_room *room, t_ways *ways)
{
	size_t 		i;
	size_t 		j;
	size_t 		k;
	size_t 		m;

	i = 0;
	j = 0;
	k = 0;
	m = 0;
	ways->total = 0;
	ways->nb_ways = 0;
	while (i < info->start->nbl && ways->steps)
	{
		if (room->ways[i]->status == 1)
		{
			while (ways->steps[j] != NULL && j < info->max_paths)
				j++;
			if (!(ways->steps[j] = ft_memalloc(sizeof(t_room) * info->end->weight)))
				error_exit(11, "Can't malloc ways->steps");
			ways->steps[j + 1] = NULL;
			m = i;
			while (room != info->end)
			{
				while (room->ways[m]->status != 1)
					m++;
				room = room->ways[m]->dest;
				room->opti = 1;
				ways->steps[j][k] = room;
				k++;
				ways->steps[j][k] = NULL;
				m = 0;

			}
			ways->total = ways->total + k;
			k = 0;
			room = info->start;
		}
		i++;
	}
	ways->nb_ways = j;
	ways->total = (ways->total + info->ant_nb - 1) / (ways->nb_ways + 1);
	return (TRUE);
}
