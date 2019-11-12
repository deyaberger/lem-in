/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_result.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:17:03 by dberger           #+#    #+#             */
/*   Updated: 2019/11/12 14:35:48 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int	ft_last_ant_in_path(t_ways *best, int i, int j)
{
	if (best->path_info[i][ANTS_SENT] == best->path_info[i][ANTS])
		j = best->path_info[i][LENGTH] - 1;
	else
	{	
		while (best->steps[i][j]->ant_index != 0)
			j++;
		if (j > 0)
			j--;
	}
	return (j);
}

t_ways	*ft_move_ants(t_info info, t_ways *best, int i, int *j)
{
	while (*j >= 0)
	{
		if (best->steps[i][*j] == info.end)
			*j -= 1;
		if (best->steps[i][*j + 1] && best->steps[i][*j + 1] != info.end && best->steps[i][*j]->ant_index != 0)
		{
			best->steps[i][*j + 1]->ant_index = best->steps[i][*j]->ant_index;
			best->steps[i][*j]->ant_index = 0;
		}
		else if (best->steps[i][*j + 1] && best->steps[i][*j + 1] == info.end && best->steps[i][*j]->ant_index != 0)
		{
			best->path_info[i][ANT_ARRIVED] = best->steps[i][*j]->ant_index;
			best->steps[i][*j]->ant_index = 0;
		}
		*j -= 1;
	}
	if (*j < 0)
		*j += 1;
	return (best);
}

t_ways	*ft_new_ants(t_ways *best, int *a, int *i, int j)
{
	t_room *room;

	room = NULL;
	if (best->path_info[*i][ANTS_SENT] < best->path_info[*i][ANTS])
	{
		room = best->steps[*i][j];
		room->ant_index = *a;
		best->path_info[*i][ANTS_SENT] += 1;
		*a += 1;
	}
	*i += 1;
	return (best);
}

void	ft_print_result(t_info *info, t_ways **best)
{
	int i;
	int j;
	t_room *room;

	i = 0;
	j = 0;
	room = NULL;
	while (i < (*best)->nb_ways && info->end->ant_index != info->ant_nb)
	{
		j = 0;
		while (j < (*best)->path_info[i][LENGTH])
		{
			room = (*best)->steps[i][j];
			if (room->ant_index != 0)
				ft_printf("L%d-%s ", room->ant_index, room->name);
			else if (room == info->end && (*best)->path_info[i][ANT_ARRIVED] != 0)
			{
				ft_printf("L%d-%s ", (*best)->path_info[i][ANT_ARRIVED], room->name);
				if ((*best)->path_info[i][ANT_ARRIVED] == info->ant_nb)
					info->end->ant_index = info->ant_nb;
				(*best)->path_info[i][ANT_ARRIVED] = 0;
			}
			j++;
		}
		i++;
	}
	ft_printf("\n");

}

void	ft_result(char *str, t_info info, t_ways *best)
{
	int i;
	int j;
	int a;
	int total;

	i = 0;
	j = 0;
	a = 1;
	total = 0;
	ft_printf("%s\n", str);	
	free(str);
	while (info.end->ant_index != info.ant_nb)
	{
		while (i < best->nb_ways)
		{
			j = ft_last_ant_in_path(best, i, j);
			best = ft_move_ants(info, best, i, &j);
			best = ft_new_ants(best, &a, &i, j);
		}
		ft_print_result(&info, &best);
		i = 0;
		j = 0;
		total++;
	}
//	ft_printf("\ntotal lignes = %d\n", total);
}
