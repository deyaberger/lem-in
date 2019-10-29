/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:36:09 by dberger           #+#    #+#             */
/*   Updated: 2019/10/29 19:32:11 by dberger          ###   ########.fr       */
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

void	ft_count_total(t_ways **ways, t_info *info, size_t j, int mode)
{
	size_t	ants;
	size_t	i;
	size_t	tpl;
	size_t	f;
	size_t	t;
	size_t	nb;
	size_t	s;
	size_t	left;

	i = 0;
	f = 0;
	t = 0;
	nb = 0;
	s = 0;
	left = 0;
	ants = info->ant_nb;
	tpl = (*ways)->tot_pl;
	if (mode == INIT)
	{
		(*ways)->tot_max = 0;
		(*ways)->min = 4294967295;
		(*ways)->tot_pl = 0;
		(*ways)->nb_ways = 0;
	}
	else if (mode == FINISH)
	{
		(*ways)->nb_ways = j + 1;
		while (i < j + 1)
		{
			ft_printf("pour path n_: [%d], ", i);
			t = (*ways)->path_info[i][LENGTH];
			ft_printf("ants = %d, tpl = %d, nb_ways = %d, t=%d  ==> ", ants, tpl, j+1, t);
			f = ((ants + tpl - ((j + 1) * t)) / (j + 1));
			(*ways)->path_info[i][ANTS] = f;
			nb = nb + f;
			s = t + f - 1;
			(*ways)->path_info[i][STEPS] = s;
			if (s > (*ways)->tot_max)
				(*ways)->tot_max = s;
			if (s < (*ways)->min)
				(*ways)->min = s;
			ft_printf(" ANTS = %d, STEPS = %d\n", f, (*ways)->path_info[i][STEPS]);
			i++;
		}
		if (nb < ants)
			left = ants - nb;
			
		ft_printf("tot max = %d, min = %d, nb = %d\n", (*ways)->tot_max, (*ways)->min, nb);
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
	ft_printf("chemin n_%d:\n", j);
	while (*room != info->end)
	{
		ft_find_room(room, m);
		(*ways)->steps[j][k] = *room;
		ft_printf("%s ", (*room)->name);
		k++;
		(*ways)->steps[j][k] = NULL;
		m = 0;
	}
	ft_printf("   LENGTH = %d\n\n", k);
	(*ways)->path_info[j][LENGTH] = k;
	(*ways)->tot_pl = (*ways)->tot_pl + k;
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
