/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_karp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:00:23 by dberger           #+#    #+#             */
/*   Updated: 2019/10/28 16:20:52 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void	ft_clean_steps(t_ways *ways, int mode)
{
	size_t j;
	size_t k;

	j = 0;
	k = 0;
	while (j <= ways->nb_ways && ways->steps[j] != NULL)
	{
		while (ways->steps[j][k] != NULL)
		{
			ways->steps[j][k] = NULL;
			k++;
		}
		if (mode == 1 || mode == 2)
		{	
			free(ways->steps[j]);
			ways->steps[j] = NULL;
		}
		k = 0;
		j++;
	}
	ways->nb_ways = 0;
	if (mode == 1 && ways->steps != NULL)
		free(ways->steps);
}

void	ft_new_best(t_info *info, t_ways *best, t_ways *comp)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	(void)info;
	while (comp->steps[j] && j <= comp->nb_ways)
	{
		while (comp->steps[j][k])
			k++;
		if (!(best->steps[j] = ft_memalloc(sizeof(t_room) * k)))
			error_exit(12, "Can't malloc best->steps");
		k = 0;
		while (comp->steps[j][k])
		{
			best->steps[j][k] = comp->steps[j][k];
			k++;
		}
		best->nb_ways = j;
		k = 0;
		j++;
	}
	ft_clean_steps(comp, 2);

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
		ft_clean_steps(best, 2);
		ft_new_best(info, best, comp);
	}
}
