/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:36:09 by dberger           #+#    #+#             */
/*   Updated: 2019/10/22 15:36:12 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

BOOL	ft_steps(t_info *info, t_room *room, t_ways *comp)
{
	size_t 		i;
	size_t 		j;
	size_t 		k;
	size_t 		m;

	i = 0;
	j = 0;
	k = 0;
	m = 0;
	comp->total = 0;
	comp->nb_ways = 0;
	while (i < info->start->nbl && comp->steps)
	{
		if (room->ways[i]->status == 1)
		{
			while (comp->steps[j] != NULL && j < info->max_paths)
				j++;
			if (!(comp->steps[j] = ft_memalloc(sizeof(t_room) * info->end->weight)))
			return (FALSE);
			comp->steps[j + 1] = NULL;
			m = i;
			while (room != info->end)
			{
				while (room->ways[m]->status != 1)
					m++;
				room = room->ways[m]->dest;
				room->opti = 1;
				comp->steps[j][k] = room;
				k++;
				comp->steps[j][k] = NULL;
				m = 0;

			}
			comp->total = comp->total + k;
			k = 0;
			room = info->start;
		}
		i++;
	}
	comp->nb_ways = j;
	comp->total = (comp->total + info->ant_nb - 1) / (comp->nb_ways + 1);
	return (TRUE);
}
