/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:13:51 by dberger           #+#    #+#             */
/*   Updated: 2019/10/30 19:12:58 by dberger          ###   ########.fr       */
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

// seulement pour faire des tests //

void		ft_print_best(t_ways best)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i <= best.nb_ways && best.steps[i] != NULL)
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

////

t_ways		ft_init_steps(size_t size)
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
	if (!(best.path_info = ft_memalloc(sizeof(size_t*) * info->max_paths)))
		error_exit(11, "Can't malloc best.way_info");
	if (!(comp.path_info = ft_memalloc(sizeof(size_t*) * info->max_paths)))
		error_exit(11, "Can't malloc comp.way_info");
	while (i < info->max_paths)
	{
		room = info->start;
		if (queue != NULL)
			queue = ft_init_var(room, queue);
		ft_shorter_way(info, &room, &queue);
		if (info->end->q == 0)
			return (NO_MORE_STEPS);
		ft_finish_queue(info, &room, &queue);
		ft_karp(info, room, &best, &comp);
		i++;
	}
	ft_print_best(best);
	ft_clean_steps(&best, 1);
	ft_clean_steps(&comp, 1);
	return (TRUE);
}
