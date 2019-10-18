/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_steps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:19:36 by dberger           #+#    #+#             */
/*   Updated: 2019/10/18 14:45:27 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int8_t	ft_steps(t_info *t, t_room *r, t_ways *comp)
{
	int 		i;
	int 		j;
	int 		k;
	int 		m;

	i = 0;
	j = 0;
	k = 0;
	m = 0;
	comp->total = 0;
	comp->nb_ways = 0;
	while (i < t->start->nbl && comp->steps)
	{
		if (r->ways[i]->status == 1)
		{
			while (comp->steps[j] != NULL && j < t->max_paths)
				j++;
			if (!(comp->steps[j] = ft_memalloc(sizeof(t_room) * t->end->weight)))
			return (0);
			comp->steps[j + 1] = NULL;
			m = i;
			while (r != t->end)
			{
				while (r->ways[m]->status != 1)
					m++;
				r = r->ways[m]->dest;
				r->opti = 1;
				comp->steps[j][k] = r;
				k++;
				comp->steps[j][k] = NULL;
				m = 0;

			}
			comp->total = comp->total + k;
			k = 0;
			r = t->start;
		}
		i++;
	}
	comp->nb_ways = j;
	comp->total = (comp->total + t->ant_nb - 1) / (comp->nb_ways + 1);
	return (1);
}
