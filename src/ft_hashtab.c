/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:17:46 by dberger           #+#    #+#             */
/*   Updated: 2019/12/03 17:33:20 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		ft_hashage(char *name, int hash_size)
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

t_room	*ft_init_tab(t_info *info)
{
	int		i;
	t_room	*room;

	i = 0;
	info->size_tab = info->room_nb * SIZE_HASH;
	if (!(info->tab = malloc(sizeof(info->tab) * info->size_tab)))
		return (NULL);
	room = info->first;
	while (i < info->size_tab)
	{
		info->tab[i] = NULL;
		i++;
	}
	return (room);
}

BOOL	ft_init_links_tab(t_info *info, t_room *room, int i)
{
	int	j;

	j = 0;
	info->tab[i] = room;
	if (!(room->link = malloc(sizeof(room->link) * info->room_nb)))
		return (FALSE);
	while (j < info->room_nb)
	{
		room->link[j] = NULL;
		j++;
	}
	if (room == info->start)
		info->start = room;
	else if (room == info->end)
		info->end = room;
	return (TRUE);
}

int		ft_coll(t_info *info, char *name, int i, int s)
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

BOOL	ft_hashtab(t_info *info, t_room *room, int i)
{
	i = 0;
	if ((room = ft_init_tab(info)) == NULL)
		return (FALSE);
	while (room)
	{
		i = ft_hashage(room->name, info->size_tab);
		if (i < info->size_tab && info->tab[i] == NULL)
		{
			if (ft_init_links_tab(info, room, i) == FALSE)
				return (FALSE);
		}
		else
		{
			i = ft_coll(info, room->name, i, info->size_tab);
			if (info->tab[i] != NULL
			&& !(ft_strcmp(room->name, info->tab[i]->name)))
				return (FALSE);
			else if (info->tab[i] == NULL)
				if (ft_init_links_tab(info, room, i) == FALSE)
					return (FALSE);
		}
		room = room->next;
	}
	return (TRUE);
}
