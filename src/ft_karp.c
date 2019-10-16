/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_karp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:00:23 by dberger           #+#    #+#             */
/*   Updated: 2019/10/16 17:44:51 by dberger          ###   ########.fr       */
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
		if (r->ways[i]->status == 1 && r->ways[i]->dest->opti == 0)
		{
			while (w->steps[j] != NULL)
				j++;
			ft_printf("j= %d\n", j);
			w->steps[j] = ft_memalloc(sizeof(t_room) * t->end->weight);
			m = i;
			while (r != t->end)
			{
				while (r->ways[m]->status != 1)
					m++;
				r = r->ways[m]->dest;
				if (r == t->end || (r != t->end && r->opti == 0))
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

t_ways		*ft_karp(t_struct *t, t_room *r, t_ways *w)
{
	int	i;
	t_link	*link;
	
	i = 0;
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
		else if (link->status == -1 && link->rev->status == 1)
		{
			link->status = 0;
			link->rev->status = 0;
		}
		r = r->mum;
	}
	w = ft_stock_steps(t, r, w);
	i = 0;
	if (w->steps[2])
	{
		while (w->steps[2][i])
		{
			ft_printf("%s, ", w->steps[2][i]->name);
			i++;
		}	
	}
	return (w);
		
}
