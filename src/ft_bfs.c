/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:59:22 by dberger           #+#    #+#             */
/*   Updated: 2019/11/19 18:11:36 by dberger          ###   ########.fr       */
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

t_ways		ft_init_steps(int size)
{
	t_ways	ways;

	if (!(ways.steps = ft_memalloc(sizeof(t_room*) * size)))
		error_exit(7, "Can't malloc t_ways->steps");
	ways.nb_ways = NEVER_FILLED;
	return (ways);
}

void		ft_shorter_way(t_info *info, t_room **room, t_room **queue)
{
	while (info->end->in_q == NOT_IN_QUEUE && *room)
	{
		*queue = ft_weight(info, *room, *queue);
		*room = (*room)->next;
	}
}

void		ft_finish_queue(t_info *info, t_room **room, t_room **queue)
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

t_ways	ft_bfs(t_info *info, t_room *room)
{
	t_room	*queue;
	t_ways	best;
	t_ways	comp;
	int	i;

	i = 0;
	queue = NULL;
	best = ft_init_steps(info->max_paths);
	comp = ft_init_steps(info->max_paths);
	if (!(best.path_info = ft_memalloc(sizeof(int*) * info->max_paths)))
		error_exit(11, "Can't malloc best.way_info");
	if (!(comp.path_info = ft_memalloc(sizeof(int*) * info->max_paths)))
		error_exit(11, "Can't malloc comp.way_info");
	while (i < info->max_paths && i < info->ant_nb)
	{
		room = info->start;
		if (queue != NULL)
			queue = ft_init_var(room, queue);
		room->in_q = 1;
		ft_shorter_way(info, &room, &queue);
		if (info->end->in_q == NOT_IN_QUEUE)
			return (best);
		ft_finish_queue(info, &room, &queue);
		if (ft_karp(info, room, &best, &comp) == KEEP_SEARCHING)
			i++;
		else
		{
			ft_clean_steps(&comp, 1);
			return (best);
		}
	}
	ft_clean_steps(&comp, 1);
	return (best);
}
