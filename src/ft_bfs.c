/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:59:22 by dberger           #+#    #+#             */
/*   Updated: 2019/11/26 14:05:46 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

t_room	*ft_init_var(t_info *info, t_room *room, t_room *queue)
{
	t_room	*save;

	room = info->start;
	queue = room;
	save = queue;
	while (queue)
	{
		room = queue;
		room->in_q = NOT_IN_QUEUE;
		room->weight = 0;
		room->mum = NULL;
		queue = (queue)->next;
	}
	queue = save;
	queue->next = NULL;
	queue = NULL;
	return (queue);
}

t_ways	ft_init_steps(int size)
{
	t_ways	ways;

	if (!(ways.steps = ft_memalloc(sizeof(t_room*) * size)))
		return (ways);
	ways.nb_ways = NEVER_FILLED;
	if (!(ways.path_info = ft_memalloc(sizeof(int*) * size)))
		return (ways);
	return (ways);
}

void	ft_finish_queue(t_info *info, t_room **room, t_room **queue)
{
	while (*room && info->end->in_q == IN_QUEUE)
	{
		if ((*room) == info->end && (*room)->next)
			*room = (*room)->next;
		if ((*room)->weight <= info->end->weight - 1)
			*queue = ft_weight(info, *room, *queue);
		else
			return ;
		*room = (*room)->next;
	}
}

BOOL	ft_shorter_way(t_info *info, t_room **room, t_room **queue)
{
	*room = info->start;
	(*room)->in_q = IN_QUEUE;
	while (info->end->in_q == NOT_IN_QUEUE && *room)
	{
		*queue = ft_weight(info, *room, *queue);
		*room = (*room)->next;
	}
	if (info->end->in_q == NOT_IN_QUEUE)
		return (STOP);
	ft_finish_queue(info, room, queue);
	return (KEEP_SEARCHING);
}

t_ways	ft_bfs(t_info *info, t_room *room, t_ways best)
{
	t_room	*queue;
	t_ways	comp;
	int		i;

	i = 0;
	queue = NULL;
	best = ft_init_steps(info->max_paths);
	comp = ft_init_steps(info->max_paths);
	if (!best.steps || !comp.steps)
		return (best);
	while (i < info->max_paths && i < info->ant_nb)
	{
		if (VISU == 1)
			ft_printf("#B\n");
		if (queue != NULL)
			queue = ft_init_var(info, room, queue);
		if (ft_shorter_way(info, &room, &queue) == STOP)
			return (best);
		if (ft_karp(info, room, &best, &comp) == STOP)
			return (best);
		i++;
	}
	ft_clean_steps(&comp, FINAL_FREE);
	return (best);
}
