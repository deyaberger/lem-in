/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:16:59 by dberger           #+#    #+#             */
/*   Updated: 2019/10/22 14:45:58 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

t_link	*ft_create_ways(t_room *from, t_room *dest, t_info *info)
{
	t_link	*link;

	if (!(link = ft_memalloc(sizeof(t_link) * info->room_nb)))
		error_exit(7, "Can't malloc t_link");
	link->dest = dest;
	link->status = 0;
	from->nbl += 1;
	return (link);
}

BOOL	ft_fill_links(t_room *one, t_room *two, t_info *info)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (one->ways[i] != NULL
			&& i < info->room_nb && one->ways[i]->dest != two)
		i++;
	if (one->ways[i] == NULL)
		one->ways[i] = ft_create_ways(one, two, info);
	else if (one->ways[i]->dest == two)
		return (FALSE);
	while (two->ways[j] != NULL
			&& j < info->room_nb && two->ways[j]->dest != one)
		j++;
	if (two->ways[j] == NULL)
		two->ways[j] = ft_create_ways(two, one, info);
	else if (two->ways[j]->dest == one)
		return (FALSE);
	one->ways[i]->rev = two->ways[j];
	two->ways[j]->rev = one->ways[i];
	return (TRUE);
}

BOOL	ft_calc_links(char *room1, char *room2, size_t s, t_info *info)
{
	size_t	h1;
	size_t	h2;
	t_room	*one;
	t_room	*two;

	h1 = ft_coll(info, room1, ft_hashage(room1, s), s);
	h2 = ft_coll(info, room2, ft_hashage(room2, s), s);
	if (info->tab[h1] == NULL || info->tab[h2] == NULL)
		return (FALSE);
	one = info->tab[h1];
	two = info->tab[h2];
	ft_fill_links(one, two, info);
	free(info->line);
	return (TRUE);
}

BOOL	ft_cut_room(t_info *info)
{
	char	*room1;
	char	*room2;
	size_t	s;

	s = 0;
	room1 = info->line;
	room2 = info->line;
	while (*room2 != '-' && *room2)
		room2++;
	room2++;
	while (room1[s] != '-' && room1[s])
		s++;
	room1[s] = '\0';
	s = info->room_nb * 10;
	if (!(ft_calc_links(room1, room2, s, info)))
		return (FALSE);
	return (TRUE);
}

BOOL	ft_links(t_info *info)
{
	if (!(ft_cut_room(info)))
		return (FALSE);
	while (get_next_line(0, &info->line))
	{
		if (info->line[0] == '#' && info->line[1] == '#')
		{
			free(info->line);
			return (FALSE);
		}
		if (info->line[0] != '#')
			if (!(ft_cut_room(info)))
				return (FALSE);
	}
	if (info->line)
		free(info->line);
	return (TRUE);
}
