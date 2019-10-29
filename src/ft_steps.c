/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:36:09 by dberger           #+#    #+#             */
/*   Updated: 2019/10/29 15:34:33 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

size_t	ft_create_space(t_ways **ways, t_info *info, size_t j)
{
	while ((*ways)->steps[j] != NULL && j < info->max_paths)
		j++;
	if (!((*ways)->steps[j] = ft_memalloc(sizeof(t_room) * info->end->weight)))
		error_exit(11, "Can't malloc ways->steps");
	(*ways)->steps[j + 1] = NULL;
	return (j);
}

void	ft_find_room(t_room **room, size_t m)
{
	while ((*room)->link[m]->status != GOOD_PATH)
		m++;
	(*room) = (*room)->link[m]->dest;
	(*room)->opti = 1;
}

void	ft_count_total(t_ways **ways, t_info *info, size_t j, int mode)
{
	size_t	ants;

	ants = info->ant_nb;
	if (mode == INIT)
	{
		(*ways)->total = 0;
		(*ways)->nb_ways = 0;
	}
	else if (mode == FINISH)
	{
		(*ways)->nb_ways = j;
		(*ways)->total = ((*ways)->total + ants - 1) / ((*ways)->nb_ways + 1);
	}
}

size_t	ft_fill_space(t_room **room, t_info *info, t_ways **ways, size_t i)
{
	size_t	m;
	size_t	j;
	size_t	k;

	m = i;
	j = 0;
	k = 0;
	j = ft_create_space(ways, info, j);
	while (*room != info->end)
	{
		ft_find_room(room, m);
		(*ways)->steps[j][k] = *room;
		k++;
		(*ways)->steps[j][k] = NULL;
		m = 0;
	}
	(*ways)->total = (*ways)->total + k;
	k = 0;
	*room = info->start;
	return (j);
}

void	ft_steps(t_info *info, t_room *room, t_ways *ways)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ft_count_total(&ways, info, j, INIT);
	while (i < info->start->nbl && ways->steps)
	{
		if (room->link[i]->status == GOOD_PATH)
			j = ft_fill_space(&room, info, &ways, i);
		i++;
	}
	ft_count_total(&ways, info, j, FINISH);
}
