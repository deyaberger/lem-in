/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:13:51 by dberger           #+#    #+#             */
/*   Updated: 2019/10/22 13:05:57 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

t_room		*ft_init_var(t_room *room, t_room *queue)
{
	t_room	*save;

	queue = room;
	save = queue;
	while (queue)
	{
		room = queue;
		room->weight = 0;
		room->q = 0;
		room->used = 0;
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

t_ways		ft_init_steps(size_t size)
{
	t_ways	ways;

	if (!(ways.steps = ft_memalloc(sizeof(t_room*) * size)))
		error_exit(7, "Can't malloc t_ways->steps");
	return (ways);
}

BOOL		ft_bfs(t_info *info, t_room *room)
{
	t_room	*queue;
	t_ways	best;
	t_ways	comp;
	size_t	i;

	i = 0;
	queue = NULL;
	best = ft_init_steps(info->max_paths);
	comp = ft_init_steps(info->max_paths);
	while (i < info->max_paths)
	{
		room = info->start;
		if (queue != NULL)
			queue = ft_init_var(room, queue);
		while (info->end->q == 0 && room)
		{
			queue = ft_weight(info, room, queue);
			room = room->next;
		}
		if (info->end->q == 0)
			return (NO_MORE_STEPS);
		while (info->end->q == 1 && room)
		{
			if (room->weight < info->end->weight - 1)
				queue = ft_weight(info, room, queue);
			room = room->next;
		}
		if (!(ft_karp(info, room, &best, &comp)))
			return (FALSE);
		i++;
	}
	ft_print_best(best);
	return (TRUE);
}
