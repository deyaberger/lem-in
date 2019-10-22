/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_karp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:00:23 by dberger           #+#    #+#             */
/*   Updated: 2019/10/18 14:37:17 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void	ft_clean_best(t_ways *best)
{
	int j;
	int k;

	j = 0;
	k = 0;
	while (j <= best->nb_ways)
	{
		while (best->steps[j][k] != NULL)
		{
			best->steps[j][k] = NULL;
			k++;
		}
		k = 0;
		j++;
	}

}

BOOL	ft_new_best(t_info *info, t_ways *best, t_ways *comp)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (comp->steps[j] && j <= comp->nb_ways)
	{
		if (j > best->nb_ways)
		{
			if (!(best->steps[j] = ft_memalloc(sizeof(t_room) * info->end->weight)))
			return (FALSE);
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
	return (TRUE);
}

void	ft_link_status(t_room *room)
{
	t_link	*link;
	int	i;

	i = 0;
	link = NULL;
	while (room->ways[i]->dest != room->mum)
		i++;
	link = room->ways[i];
	if (link->status == 0 && link->rev->status == 0)
	{
		link->status = -1;
		link->rev->status = 1;
	}
	else if (link->status == 1 && link->rev->status == -1)
	{
		link->status = 0;
		link->rev->status = 0;
	}
}

BOOL	ft_karp(t_info *info, t_room *room, t_ways *best, t_ways *comp)
{
	room = info->end;
	while (room != info->start)
	{
		ft_link_status(room);
		room = room->mum;
	}
	if (best->steps[0] == NULL)
		ft_steps(info, room, best);
	else
		ft_steps(info, room, comp);
	if (comp->steps[0] != NULL  && comp->total < best->total)
	{
		ft_clean_best(best);
		if (!(ft_new_best(info, best, comp)))
			return (FALSE);
	}
	return (TRUE);
}
