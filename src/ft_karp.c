/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_karp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:00:23 by dberger           #+#    #+#             */
/*   Updated: 2019/10/17 18:16:00 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

t_ways		*ft_karp(t_struct *t, t_room *r, t_ways *best, t_ways *comp)
{
	int	i;
	int	j;
	int	k;
	t_link	*link;
	
	i = 0;
	j = 0;
	k = 0;
	r = t->end;
	link = NULL;
	while (r != t->start)
	{
		i = 0;
		while (r->ways[i]->dest != r->mum)
			i++;
		link = r->ways[i];
		if (link->status == 0 && link->rev->status == 0)
		{
			link->status = -1;
			link->rev->status = 1;
		}
		else if (link->status == 1 && link->rev->status == -1)
		{
			link->status = 0;
			link->rev->status = 0;
		}
		r = r->mum;
	}
	if (best->steps[0] == NULL)
		best = ft_steps(t, r, best);
	else
		comp = ft_steps(t, r, comp);
	j = 0;
	k = 0;
	if (comp->steps[0] != NULL  && comp->total < best->total)
	{
		while (j <= best->nb_ways)
		{
			while (best->steps[j][k] != NULL)
			{
				best->steps[j][k] = NULL;
				k++;
			}
			k = 0;
			j++;
		}
		j = 0;
		while (comp->steps[j] && j <= comp->nb_ways)
		{
			if (j > best->nb_ways)
			{
				best->steps[j] = ft_memalloc(sizeof(t_room) * t->end->weight);
				best->steps[j + 1] = NULL;
			}
			while (comp->steps[j][k])
			{
				best->steps[j][k] = comp->steps[j][k];
				comp->steps[j][k] = NULL;
				k++;
			}
			comp->steps[j] = NULL;
			best->nb_ways = j;
			k = 0;
			j++;
		}
		comp->nb_ways = 0;
	}
	return (best);
		
}
