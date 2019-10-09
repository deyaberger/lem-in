/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_karp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:00:23 by dberger           #+#    #+#             */
/*   Updated: 2019/10/09 20:51:45 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

t_ways		*ft_stock_steps(t_struct *t, t_room *r, t_ways *w)
{
	int 		i;
	int 		j;
	int 		k;
	int 		m;
	
	i = 0;
	j = 0;
	k = 0;
	m = 0;
	while (i < t->start->nbl && w->steps)
	{
		if (r->ways[i]->status == 1)
		{
			while (w->steps[j] != NULL)
				j++;
			w->steps[j] = ft_memalloc(sizeof(t_room) * t->end->weight);
			m = i;
			while (r != t->end)
			{
				while (r->ways[m]->status != 1)
					m++;
				r = r->ways[m]->dest;
				r->opti = 1;
				w->steps[j][k] = r;
				k++;
				m = 0;

			}
			k = 0;
			r = t->start;
			j++;
		}
		i++;
	}
	return (w);
}

int8_t		ft_karp(t_struct *t, t_room *r, t_ways *w)
{
	int	i;
	
	i = 0;
	r = t->end;
	while (r != t->start)
	{
		while (r->ways[i]->dest != r->mum)
			i++;
		if (r->ways[i]->status == 0 && r->ways[i]->rev->status == 0)
		{
			r->ways[i]->status = -1;
			r->ways[i]->rev->status = 1;
		}
		else if (r->ways[i]->status == -1 && r->ways[i]->rev->status == 1)
		{
			r->ways[i]->status = 0;
			r->ways[i]->rev->status = 0;
		}
		r = r->mum;
	}
	w = ft_stock_steps(t, r, w);
	return (0);
		
}
