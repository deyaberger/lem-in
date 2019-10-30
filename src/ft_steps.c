/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:36:09 by dberger           #+#    #+#             */
/*   Updated: 2019/10/30 19:12:48 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

size_t	ft_create_space(t_ways **ways, t_info *info, size_t j)
{
	while ((*ways)->steps[j] != NULL && j < info->max_paths)
		j++;
	if (!((*ways)->steps[j] = ft_memalloc(sizeof(t_room) * info->end->weight)))
		error_exit(11, "Can't malloc ways->steps");
	if (!((*ways)->path_info[j] = ft_memalloc(sizeof(size_t) * 3)))
		error_exit(11, "Can't malloc way->path_info");
	(*ways)->path_info[j][LENGTH] = NONE;
	(*ways)->path_info[j][ANTS] = NONE;
	(*ways)->path_info[j][STEPS] = NONE;
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
	(*ways)->path_info[j][LENGTH] = k;
	(*ways)->tot_pl = (*ways)->tot_pl + k;
	k = 0;
	*room = info->start;
	return (j);
}

void	ft_init_ways(t_ways **ways)
{
	(*ways)->tot_max = 0;
	(*ways)->min = 4294967295;
	(*ways)->tot_pl = 0;
}

t_ways	*ft_steps(t_info *info, t_room *room, t_ways *ways)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ft_init_ways(&ways);
	while (i < info->start->nbl && ways->steps)
	{
		if (room->link[i]->status == GOOD_PATH)
			j = ft_fill_space(&room, info, &ways, i);
		i++;
	}
	ways = ft_calc_steps(ways, info, j);
	return (ways);
}
