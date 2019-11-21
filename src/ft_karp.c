/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_karp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:00:23 by dberger           #+#    #+#             */
/*   Updated: 2019/11/21 15:45:14 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

t_ways	*ft_copy_comp(int j, t_ways *best, t_ways *comp)
{
	int k;

	k = 0;
	best->nb_ways = comp->nb_ways;
	best->tot_max = comp->tot_max;
	best->tot_pl = comp->tot_pl;
	best->min = comp->min;
	while (comp->steps[j][k])
	{
		if (k < 5)
			best->path_info[j][k] = comp->path_info[j][k];
		comp->steps[j][k]->opti = 1;
		best->steps[j][k] = comp->steps[j][k];
		k++;
	}
	return (best);
}

BOOL	ft_new_best(t_ways *best, t_ways *comp)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (comp->steps[j] && j <= comp->nb_ways)
	{
		k = comp->path_info[j][LENGTH];
		if (!(best->steps[j] = ft_memalloc(sizeof(t_room) * k)))
			return (FALSE);
		if (!(best->path_info[j] = ft_memalloc(sizeof(int) * 5)))
			return (FALSE);
		best = ft_copy_comp(j, best, comp);
		j++;
	}
	return (TRUE);
}

void	ft_update_status(t_room *room)
{
	t_link	*link;
	int		i;

	i = 0;
	link = NULL;
	while (room->link[i] && room->link[i]->dest != room->mum)
		i++;
	link = room->link[i];
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

BOOL	ft_karp(t_info *info, t_room *room, t_ways *best, t_ways *comp)
{
	room = info->end;
	while (room != info->start)
	{
		ft_update_status(room);
		room = room->mum;
	}
	if (best->nb_ways == NEVER_FILLED)
	{
		if (!(best = ft_steps(info, room, best)))
			return (STOP);
	}
	else
	{
		if (!(comp = ft_steps(info, room, comp)))
		{
			ft_clean_steps(comp, 2);
			return (STOP);
		}
	}
	if (comp->nb_ways != NEVER_FILLED
		&& comp->tot_max < best->tot_max && comp->tot_max != -1)
	{
		ft_clean_steps(best, 0);
		if (ft_new_best(best, comp) == FALSE)
		{
			ft_clean_steps(comp, 2);
			return (STOP);
		}
		ft_clean_steps(comp, 2);
		return (KEEP_SEARCHING);
	}
	else if (comp->nb_ways != NEVER_FILLED
		&& (comp->tot_max > best->tot_max || comp->tot_max == -1))
	{
		ft_clean_steps(comp, 2);
		return (STOP);
	}
	return (KEEP_SEARCHING);
}
