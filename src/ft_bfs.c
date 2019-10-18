/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:13:51 by dberger           #+#    #+#             */
/*   Updated: 2019/10/18 14:28:02 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

t_room		*ft_init_var(t_room *r, t_room *queue)
{
	t_room	*save;

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

void		ft_print_best(t_ways best)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (best.steps[i] != NULL)
	{
		while (best.steps[i][j] != NULL)
		{
			ft_printf("%s, ", best.steps[i][j]->name);
			j++;
		}
		ft_printf("\n");
		j = 0;
		i++;
	}
}

int8_t		ft_bfs(t_struct *t, t_room *r)
{
	t_room	*queue;
	t_ways	best;
	t_ways	comp;
	int	i;

	i = 0;
	queue = NULL;
	if (t->start->nbl <= t->end->nbl)
		t->max_paths = t->start->nbl;
	else
		t->max_paths = t->end->nbl;
	best.steps = ft_memalloc(sizeof(t_room*) * t->max_paths);
	comp.steps = ft_memalloc(sizeof(t_room*) * t->max_paths);
	while (i < t->max_paths)
	{
		r = t->start;
		if (queue != NULL)
			queue = ft_init_var(r, queue);
		while (t->end->q == 0)
		{
			queue = ft_weight(t, r, queue);
			r = r->next;
		}
		while (t->end->q == 1 && r)
		{
			if (r->weight < t->end->weight - 1)
				queue = ft_weight(t, r, queue);
			r = r->next;
		}
		ft_karp(t, r, &best, &comp);
		i++;
	}
	ft_print_best(best);
	return (1);
}
