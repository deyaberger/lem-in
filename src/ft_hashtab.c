/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:17:46 by dberger           #+#    #+#             */
/*   Updated: 2019/10/22 11:38:54 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

size_t	ft_hashage(char *name, int hash_size)
{
	size_t	i;
	size_t	hash;

	i = 0;
	hash = 0;
	while (i != ft_strlen(name))
	{
		hash += name[i++];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return (hash % hash_size);
}

void	ft_init_tab(t_info *info, size_t s)
{
	size_t	i;

	i = 0;
	while (i < s)
	{
		info->tab[i] = NULL;
		i++;
	}
}

void	ft_init_links_tab(t_info *info, t_room *room, int i)
{
	size_t	j;

	j = 0;
	info->tab[i] = room;
	if (!(room->link = ft_memalloc(sizeof(room->link) * info->room_nb)))
		error_exit(4, "Can't malloc room->link");
	while (j < info->room_nb)
	{
		room->link[j] = NULL;
		j++;
	}
	if (room->type == ROOM_START)
		info->start = room;
	else if (room->type == ROOM_END)
		info->end = room;
}

size_t	ft_coll(t_info *info, char *name, size_t i, size_t s)
{
	while (i < s && info->tab[i] != NULL
		&& ft_strcmp(name, info->tab[i]->name))
	{
		i++;
		if (i == s)
			i = 0;
	}
	return (i);
}

void	ft_hashtab(t_info *info, t_room *room)
{
	size_t	i;
	size_t	s;

	i = 0;
	s = info->room_nb * 10;
	if (!(info->tab = ft_memalloc(sizeof(info->tab) * s)))
		error_exit(3, "Can't malloc info->tab");
	ft_init_tab(info, s);
	room = info->first;
	while (room)
	{
		i = ft_hashage(room->name, s);
		if (i < s && info->tab[i] == NULL)
			ft_init_links_tab(info, room, i);
		else
		{
			i = ft_coll(info, room->name, i, s);
			if (info->tab[i] != NULL
			&& !(ft_strcmp(room->name, info->tab[i]->name)))
				error_exit(5, "Error in ft_coll: same room name twice");
			else if (info->tab[i] == NULL)
				ft_init_links_tab(info, room, i);
		}
		room = room->next;
	}
}
