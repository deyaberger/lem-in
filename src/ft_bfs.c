/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 12:15:02 by dberger           #+#    #+#             */
/*   Updated: 2019/10/08 11:26:08 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int8_t		ft_orient(t_struct *t, t_room *r)
{
	t_bfs	*b;
	int		i;
	int		j;

	j = 0;
	b = NULL;
	i = r->weight;
	b = ft_memalloc(sizeof(t_bfs));
	if (b == NULL)
		return (0);
	b->len = r->weight;
	b->steps = ft_memalloc(sizeof(t_room) * i);
	if (b->steps == NULL)
		return (0);
	i--;
	while (r != t->start && i >= 0)
	{
		while (r->ways[j] && r->ways[j]->dest != r->mum)
			j++;
		r->ways[j]->status = -1;
		r->ways[j]->rev->status = 1;
		b->steps[i] = r;
		r = r->ways[j]->dest;
		j = 0;
		i--;
		
	}
	return (1);
}

int		ft_bfs(t_struct *t, t_room *r)
{
	t_room *queue;
	t_room	*top;
	t_room	*ngb;
	int		i;

	r = t->start;
	r->mum = NULL;
	r->q = 1;
	i = 0;
	t->first = r;
	queue = r;
	top = r;
	queue->next = NULL;
	while (t->end->q == 0)
	{
		r->used = 1;
		while (r->ways[i])
		{
			if (r->ways[i]->dest->used != 1 && r->ways[i]->dest != r->mum
				&& r->ways[i]->dest->q != 1)
			{
				ngb = r->ways[i]->dest;
				ngb->q = 1;
				ngb->weight = r->weight + 1;
				ngb->mum = r;
				ngb->next = NULL;
				queue->next = ngb;
				queue = queue->next;
			}
			i++;
		}
		i = 0;
		if (top->next)
			r = top->next;
		top = top->next;
	}
	ft_orient(t, t->end);
	return (0);
}
