/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_weight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:50:55 by dberger           #+#    #+#             */
/*   Updated: 2019/11/28 16:31:43 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		ft_calc_weight(t_room *room, int i)
{
	int	weight;

	weight = 0;
	if (room->link[i]->status == BACKWARD)
		weight = room->weight - 1;
	else if (room->link[i]->status == UNUSED)
		weight = room->weight + 1;
	return (weight);
}

void	ft_new_in(t_room *room, t_room **queue, t_room **ngb, int weight)
{
	if ((*ngb)->in_q == NOT_IN_QUEUE)
	{
		if (VISU == 1)
			ft_printf("%s-", (*ngb)->name);
		(*ngb)->in_q = IN_QUEUE;
		(*ngb)->next = NULL;
		(*queue)->next = *ngb;
		(*queue) = *ngb;
	}
	(*ngb)->weight = weight;
	(*ngb)->mum = room;
}

BOOL	ft_check_link(t_room *ngb, t_info *info, t_room *room, int i)
{
	t_link	*link;
	int		mum;
	int		k;
	int		m;

	mum = 0;
	k = 0;
	m = 0;
	while (room->mum && room->link[m]->dest != room->mum)
		m++;
	link = room->link[i];
	if (ngb == room->mum)
		mum = i;
	if (ngb != room->mum && ngb != info->start)
		k = k | GOOD_PATH;
	if (room->opti == 0 && link->status == UNUSED)
		k = k | CLEAN;
	if (room->opti == 1 && link->status == BACKWARD
		&& room->link[m]->status == UNUSED)
		k = k | REVERSE;
	if (room->opti == 1 && room->link[m]->status == FORWARD)
		k = k | OUT;
	if ((k & GOOD_PATH) && ((k & CLEAN) || (k & REVERSE) || (k & OUT)))
		return (TRUE);
	return (FALSE);
}

void	ft_add_to_queue(t_room *room, t_room **queue, t_room **ngb, int i)
{
	int new_weight;

	new_weight = 0;
	if ((*ngb)->in_q == NOT_IN_QUEUE)
		ft_new_in(room, queue, ngb, ft_calc_weight(room, i));
	else if ((*ngb)->in_q == IN_QUEUE)
	{
		new_weight = ft_calc_weight(room, i);
		if (new_weight < (*ngb)->weight)
			ft_new_in(room, queue, ngb, new_weight);
	}
}

t_room	*ft_weight(t_info *info, t_room *room, t_room *queue)
{
	t_room	*ngb;
	int		i;

	i = 0;
	ngb = NULL;
	if (queue == NULL)
		queue = room;
	if (VISU == 1)
		ft_printf("%s:", room->name);
	while (i < room->nbl)
	{
		ngb = room->link[i]->dest;
		if (ft_check_link(ngb, info, room, i) == TRUE)
			ft_add_to_queue(room, &queue, &ngb, i);
		i++;
	}
	if (VISU == 1)
		ft_printf("\n");
	return (queue);
}
