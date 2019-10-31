/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:29:31 by dberger           #+#    #+#             */
/*   Updated: 2019/10/31 15:26:24 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void	ft_free_path_info(t_ways *ways)
{
	size_t i;

	i = 0;
	while (i < ways->nb_ways)
	{
		free(ways->path_info[i]);
		i++;
	}
}

void	ft_free_steps(t_ways *ways, int mode)
{
	size_t j;
	size_t k;

	j = 0;
	k = 0;
	while (j < ways->nb_ways && ways->steps[j] != NULL)
	{
		while (ways->steps[j][k] != NULL)
		{
			if (mode != 2)
				ways->steps[j][k]->opti = 0;
			ways->steps[j][k] = NULL;
			k++;
		}
		free(ways->steps[j]);
		ways->steps[j] = NULL;
		k = 0;
		j++;
	}
}

void	ft_clean_steps(t_ways *ways, int mode)
{
	ft_free_steps(ways, mode);
	ft_free_path_info(ways);
	ways->nb_ways = 0;
	ways->tot_max = 0;
	if (mode == 1 && ways->steps != NULL)
		free(ways->steps);
	if (mode == 1 && ways->path_info != NULL)
		free(ways->path_info);
}

size_t	ft_free_rooms(t_info *info, size_t i)
{
	t_room	*room;
	size_t	j;
	size_t	k;

	room = NULL;
	j = 0;
	k = 0;
	if (info->tab && info->tab[i] != NULL)
	{
		room = info->tab[i];
		free(room->name);
		while (j <= info->room_nb && room->link && room->link[j])
		{
			free(room->link[j]);
			j++;
		}
		free(room->link);
		free(room);
		j = 0;
	}
	i++;
	return (i);
}

void	ft_clean_free(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < info->room_nb * 10)
		i = ft_free_rooms(info, i);
	i = 0;
	while ((int)i <= info->xmax && info->coord[i])
	{
		free(info->coord[i]);
		i++;
	}
	if (info->coord)
		free(info->coord);
	if (info->tab)
		free(info->tab);
}
