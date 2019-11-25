/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:17:46 by dberger           #+#    #+#             */
/*   Updated: 2019/11/21 18:34:36 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

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

void	ft_init_tab(t_info *info, int s)
{
	int	i;

	i = 0;
	while (i < s)
	{
		info->tab[i] = NULL;
		i++;
	}
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

void	ft_clean_list(t_info *info)
{
	t_room *room;
	t_room *save;
	
	room = info->first;
	save = room;
	while (room)
	{
		ft_printf("room->name= %s\n", room->name);
		if (room->next)
			save = room->next;
		if (room->link)
		{
			ft_printf("link\n");
			free(room->link);
		}
	
		free(room->name);
		free(room);
		room = save;
	}
}

BOOL	ft_hashtab(t_info *info, t_room *room)
{
	int	i;
	int	s;

	i = 0;
	s = info->room_nb * 10;
	if (!(info->tab = malloc(sizeof(info->tab) * s)))
		return (FALSE);
	ft_init_tab(info, s);
	room = info->first;
	while (room)
	{
		i = ft_hashage(room->name, s);
		if (i < s && info->tab[i] == NULL)
		{
			if (ft_init_links_tab(info, room, i) == FALSE)
				return (FALSE);
		}
		else
		{
			i = ft_coll(info, room->name, i, s);
			if (info->tab[i] != NULL
			&& !(ft_strcmp(room->name, info->tab[i]->name)))
			{
				ft_clean_list(info);
				return (FALSE);
			}
			else if (info->tab[i] == NULL)
				if (ft_init_links_tab(info, room, i) == FALSE)
					return (FALSE);
		}
		room = room->next;
	}
	return (TRUE);
}
