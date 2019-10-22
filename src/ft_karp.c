/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_karp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:00:23 by dberger           #+#    #+#             */
/*   Updated: 2019/10/22 17:25:05 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void	ft_clean_steps(t_ways *ways, int mode)
{
	size_t j;
	size_t k;

	j = 0;
	k = 0;
	(void)mode;
	while (j <= ways->nb_ways && ways->steps[j] != NULL)
	{
		while (ways->steps[j][k] != NULL)
		{
			ways->steps[j][k] = NULL;
			k++;
		}
		if (mode == 1 && ways->steps[j] != NULL)
			free(ways->steps[j]);
		k = 0;
		j++;
	}
	if (mode == 1 && ways->steps != NULL)
		free(ways->steps);
}

void	ft_new_best(t_info *info, t_ways *best, t_ways *comp)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (comp->steps[j] && j <= comp->nb_ways)
	{
		if (j > best->nb_ways)
		{
			if (!(best->steps[j] = ft_memalloc(sizeof(t_room) * info->end->weight)))
				error_exit(8, "Can't malloc best->steps");
			best->steps[j + 1] = NULL;
		}
		while (comp->steps[j][k])
		{
			best->steps[j][k] = comp->steps[j][k];
			comp->steps[j][k] = NULL;
			k++;
		}
		comp->steps[j] = NULL;
		best->nb_ways = j;
		k = 0;
		j++;
	}
	comp->nb_ways = 0;
}

void	ft_update_status(t_room *room)
{
	t_link	*link;
	size_t	i;

	i = 0;
	link = NULL;
	while (room->ways[i]->dest != room->mum)
		i++;
	link = room->ways[i];
	if (link->status == UNUSED && link->rev->status == UNUSED)
	{
		link->status = BACKWARD;
		link->rev->status = FORWARD;
	}
	else if (link->status == FORWARD && link->rev->status == BACKWARD)
	{
		link->status = CANCELED;
		link->rev->status = CANCELED;
	}
}

void	ft_karp(t_info *info, t_room *room, t_ways *best, t_ways *comp)
{
	room = info->end;
	while (room != info->start)
	{
		ft_update_status(room);
		room = room->mum;
	}
	if (best->steps[0] == NULL)
		ft_steps(info, room, best);
	else
		ft_steps(info, room, comp);
	if (comp->steps[0] != NULL && comp->total < best->total)
	{
		ft_clean_steps(best, 0);
		ft_new_best(info, best, comp);
	}
}
