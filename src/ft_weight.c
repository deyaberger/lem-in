/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_weight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:50:55 by dberger           #+#    #+#             */
/*   Updated: 2019/10/17 18:13:41 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int	ft_calc_weight(t_room *r, int i)
{
	int	weight;

	weight = 0;
	if (r->ways[i]->status == -1)
		weight = r->weight - 1;
	else if (r->ways[i]->status == 0)
		weight = r->weight + 1;
	return (weight);
}

void	ft_new_in(t_room *r, t_room **queue, t_room **ngb, int weight)
{
	(*ngb)->weight = weight;
	(*ngb)->q = 1;
	(*ngb)->mum = r;
	(*ngb)->next = NULL;
	(*queue)->next = *ngb;
	(*queue) = *ngb;
}

t_room	*ft_weight(t_struct *t, t_room *r, t_room *queue)
{
	t_room	*ngb;
	int	i;
	int	mum;
	int	new_weight;
	t_link	*link;

	i = 0;
	mum = 0;
	new_weight = 0;
	ngb = NULL;
	r->q = 1;
	r->used = 1;
	if (queue == NULL)
		queue = r;
	while (i < r->nbl)
	{
		ngb = r->ways[i]->dest;
		link = r->ways[i];
		if (ngb == r->mum)
			mum = i;
		if ((ngb != r->mum) && (ngb != t->start)
		&& ((((link->status == 0) && (r->opti == 0))
		|| ((link->status == 0) && (r->opti == 1)
		&& (r->ways[mum]->status == 1)))
		|| ((link->status == -1) && (r->opti == 1))))
		{
			if (ngb->used == 0 && ngb->q == 0)
				ft_new_in(r, &queue, &ngb, ft_calc_weight(r, i));
			else if (ngb->used == 1 || ngb->q == 1)
			{
				new_weight = ft_calc_weight(r, i);
				if (new_weight < ngb->weight)
					ft_new_in(r, &queue, &ngb, new_weight);
			}
		}
		i++;
	}
	return (queue);
}
