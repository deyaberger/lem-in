/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:29:31 by dberger           #+#    #+#             */
/*   Updated: 2019/11/21 18:28:54 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void	ft_free_path_info(t_ways *ways)
{
	int i;

	i = 0;
	while (i < ways->nb_ways && ways->path_info && ways->path_info[i])
	{
		free(ways->path_info[i]);
		i++;
	}
}

void	ft_free_steps(t_ways *ways, int mode)
{
	int j;
	int k;

	j = 0;
	k = 0;
	while (ways->steps && j < ways->nb_ways && ways->steps[j] != NULL)
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

int	ft_free_rooms(t_info *info, int i)
{
	t_room	*room;
	int	j;
	int	k;

	room = NULL;
	j = 0;
	k = 0;
	if (info->tab && info->tab[i] != NULL)
	{
		room = info->tab[i];
		if (room->name)
			free(room->name);
		while (j <= info->room_nb && room->link && room->link[j])
		{
			free(room->link[j]);
			j++;
		}
		if (room->link)
			free(room->link);
		if (room)
			free(room);
		j = 0;
	}
	i++;
	return (i);
}

void	ft_clean_free(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->room_nb * 10)
		i = ft_free_rooms(info, i);
	i = 0;
	while (i <= info->xmax && info->coord != NULL && info->coord[i])
	{
		free(info->coord[i]);
		i++;
	}
	if (info->coord)
		free(info->coord);
	if (info->tab)
		free(info->tab);
}
