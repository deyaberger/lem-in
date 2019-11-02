/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:13:51 by dberger           #+#    #+#             */
/*   Updated: 2019/11/02 18:33:34 by dberger          ###   ########.fr       */
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

t_ways		ft_init_steps(int size)
{
	t_ways	ways;

	if (!(ways.steps = ft_memalloc(sizeof(t_room*) * size)))
		error_exit(7, "Can't malloc t_ways->steps");
	ways.nb_ways = -1;
	return (ways);
}

void		ft_shorter_way(t_info *info, t_room **room, t_room **queue)
{
	while (info->end->q == 0 && *room)
	{
		*queue = ft_weight(info, *room, *queue);
		*room = (*room)->next;
	}
}

void		ft_finish_queue(t_info *info, t_room **room, t_room **queue)
{
	while (info->end->q == 1 && *room)
	{
		if ((*room)->weight < info->end->weight - 1)
			*queue = ft_weight(info, *room, *queue);
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
		ft_shorter_way(info, &room, &queue);
		if (info->end->q == 0)
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
