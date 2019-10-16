/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:13:51 by dberger           #+#    #+#             */
/*   Updated: 2019/10/16 17:45:55 by dberger          ###   ########.fr       */
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

t_room	*ft_new_in(t_room *r, t_room *queue, t_room **ngb, int weight)
{
	(*ngb)->weight = weight;
	(*ngb)->q = 1;
	(*ngb)->mum = r;
	(*ngb)->next = NULL;
	queue->next = *ngb;
	queue = *ngb;
	return (queue);
}

t_room	*ft_put_weight(t_struct *t, t_room *r, t_room *queue, int mode)
{
	t_room	*ngb;
	int	i;
	int	j;
	int	new_weight;

	i = 0;
	j = 0;
	ngb = NULL;
	r->q = 1;
	r->used = 1;
	if (queue == NULL)
		queue = r;
	new_weight = 0;
	(void)mode;
	while (i < r->nbl)
	{
		ngb = r->ways[i]->dest;
		if (r->ways[i]->dest == r->mum)
			j = i;
		if ((ngb != r->mum) && (ngb != t->start)
		&& ((((r->ways[i]->status == 0) && (r->opti == 0))
		|| ((r->ways[i]->status == 0) && (r->opti == 1) && (r->ways[j]->status == 1)))
		|| ((r->ways[i]->status == -1) && (r->opti == 1))))
		{
			if (ngb->used == 0 && ngb->q == 0)
				queue = ft_new_in(r, queue, &ngb, ft_calc_weight(r, i));
			else if (ngb->used == 1 || ngb->q == 1)
			{
				new_weight = ft_calc_weight(r, i);
				if (new_weight < ngb->weight)
					queue = ft_new_in(r, queue, &ngb, new_weight);
			}
		}
		i++;
	}
	return (queue);
}

t_room	*ft_init_var(t_room *r, t_room *queue)
{
	t_room *save;

	queue = r;
	save = queue;
	while (queue)
	{
		r = queue;
		r->weight = 0;
		r->q = 0;
		r->used = 0;
		queue = (queue)->next;
	}
	queue = save;
	queue->next = NULL;
	queue = NULL;
	return (queue);
}

int8_t	ft_bfs(t_struct *t, t_room *r)
{	
	t_room *queue;
	t_ways	*w;
	int	max_paths;
	int	i;
	int	j;

	i = 0;
	j = 0;
	max_paths = 0;
	queue = NULL;
	w = ft_memalloc(sizeof(t_ways));
	if (t->start->nbl <= t->end->nbl)
		max_paths = t->start->nbl;
	else
		max_paths = t->end->nbl;
	w->steps = ft_memalloc(sizeof(t_room*) * max_paths);
	r = t->start;
	if (queue != NULL)
		queue = ft_init_var(r, queue);
	while (t->end->q == 0)
	{
		queue = ft_put_weight(t, r, queue, 0);
		r = r->next;
	}
	while (t->end->q == 1 && r)
	{
		if (r->weight < t->end->weight - 1)
			queue = ft_put_weight(t, r, queue, 0);
		r = r->next;
	}
	w = ft_karp(t, r, w);	

///////////////////////////////////////////////////////

	
	r = t->start;
	if (queue != NULL)
		queue = ft_init_var(r, queue);
	while (t->end->q == 0)
	{
		queue = ft_put_weight(t, r, queue, 1);
		r = r->next;
	}
	while (t->end->q == 1 && r)
	{
		if (r->weight < t->end->weight - 1)
			queue = ft_put_weight(t, r, queue, 2);
		r = r->next;
	}
	ft_printf("\n************\n\n");
	w = ft_karp(t, r, w);	

///////////////////////////////////////////////////////


	r = t->start;
	if (queue != NULL)
		queue = ft_init_var(r, queue);
	while (t->end->q == 0)
	{
		queue = ft_put_weight(t, r, queue, 3);
		r = r->next;
	}
	while (t->end->q == 1 && r)
	{
		if (r->weight < t->end->weight - 1)
			queue = ft_put_weight(t, r, queue, 4);
		r = r->next;
	}
	ft_printf("\n************\n\n");
	w = ft_karp(t, r, w);	

///////////////////////////////////////////////////////


/*	while (w->steps[i][j])
	{	
		ft_printf("%s,", w->steps[i][j]->name);
		j++;
	}	
	ft_printf("\n");*/
	return (1);
}
