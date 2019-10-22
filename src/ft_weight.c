/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_weight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:50:55 by dberger           #+#    #+#             */
/*   Updated: 2019/10/22 15:21:40 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

size_t	ft_calc_weight(t_room *room, size_t i)
{
	size_t	weight;

	weight = 0;
	if (room->ways[i]->status == -1)
		weight = room->weight - 1;
	else if (room->ways[i]->status == 0)
		weight = room->weight + 1;
	return (weight);
}

void	ft_new_in(t_room *room, t_room **queue, t_room **ngb, int weight)
{
	(*ngb)->weight = weight;
	(*ngb)->q = 1;
	(*ngb)->mum = room;
	(*ngb)->next = NULL;
	(*queue)->next = *ngb;
	(*queue) = *ngb;
}

BOOL	ft_check_link(t_room *ngb, t_info *info, t_room *room, size_t i)
{
	t_link	*link;
	size_t	mum;

	mum = 0;
	link = room->ways[i];
	if (ngb == room->mum)
		mum = i;
	if (ngb != room->mum && ngb != info->start)
		i = GOOD_PATH;
	if (room->opti == 0 && link->status == 0)
		i += CLEAN;
	if (room->opti == 1 && link->status == -1)
		i += REVERSE;
	if (room->opti == 1 && link->status == 0 && room->ways[mum]->status == -1)
		i += CONTINUE_AFTER_REVERSE;
	if (i == GOOD_PATH + CLEAN || i == GOOD_PATH + REVERSE
			|| i == GOOD_PATH + CONTINUE_AFTER_REVERSE)
		return (TRUE);
	return (FALSE);
}

void	ft_add_to_queue(t_room *room, t_room **queue, t_room **ngb, size_t i)
{
	size_t new_weight;

	new_weight = 0;
	if ((*ngb)->used == 0 && (*ngb)->q == 0)
		ft_new_in(room, queue, ngb, ft_calc_weight(room, i));
	else if ((*ngb)->used == 1 || (*ngb)->q == 1)
	{
		new_weight = ft_calc_weight(room, i);
		if (new_weight < (*ngb)->weight)
			ft_new_in(room, queue, ngb, new_weight);
	}
}

t_room	*ft_weight(t_info *info, t_room *room, t_room *queue)
{
	t_room	*ngb;
	size_t	i;

	i = 0;
	ngb = NULL;
	room->q = 1;
	room->used = 1;
	if (queue == NULL)
		queue = room;
	while (i < room->nbl)
	{
		ngb = room->ways[i]->dest;
		if (ft_check_link(ngb, info, room, i) == TRUE)
			ft_add_to_queue(room, &queue, &ngb, i);
		i++;
	}
	return (queue);
}
