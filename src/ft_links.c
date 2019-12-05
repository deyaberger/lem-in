/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:16:59 by dberger           #+#    #+#             */
/*   Updated: 2019/12/05 15:17:27 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

t_link	*ft_create_ways(t_room *from, t_room *dest, t_info *info)
{
	t_link	*link;

	if (!(link = (t_link*)malloc(sizeof(t_link) * info->room_nb)))
		return (NULL);
	link->dest = dest;
	link->status = 0;
	from->nbl += 1;
	info->link_nb = info->link_nb + 1;
	return (link);
}

BOOL	ft_fill_links(t_room *one, t_room *two, t_info *info, int i)
{
	int	j;

	j = 0;
	if (one->link[i] == NULL)
	{
		if (!(one->link[i] = ft_create_ways(one, two, info)))
			return (FALSE);
	}
	else if (one->link[i]->dest == two)
		return (FALSE);
	while (two->link[j] != NULL
			&& j < info->room_nb && two->link[j]->dest != one)
		j++;
	if (two->link[j] == NULL)
	{
		if (!(two->link[j] = ft_create_ways(two, one, info)))
			return (FALSE);
	}
	else if (two->link[j]->dest == one)
		return (FALSE);
	one->link[i]->rev = two->link[j];
	two->link[j]->rev = one->link[i];
	return (TRUE);
}

BOOL	ft_calc_links(char *room1, char *room2, int s, t_info *info)
{
	int		i;
	int		h1;
	int		h2;
	t_room	*one;
	t_room	*two;

	i = 0;
	h1 = ft_coll(info, room1, ft_hashage(room1, s), s);
	h2 = ft_coll(info, room2, ft_hashage(room2, s), s);
	if (info->tab[h1] == NULL || info->tab[h2] == NULL)
		return (FALSE);
	one = info->tab[h1];
	two = info->tab[h2];
	while (one->link[i] != NULL
			&& i < info->room_nb && one->link[i]->dest != two)
		i++;
	ft_fill_links(one, two, info, i);
	free(info->line);
	return (TRUE);
}

BOOL	ft_cut_room(t_info *info)
{
	char	*room1;
	char	*room2;
	int		s;

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
	if (!room2 || !room1)
		return (FALSE);
	if (!(ft_calc_links(room1, room2, s, info)))
		return (FALSE);
	return (TRUE);
}

BOOL	ft_links(t_info *info, char **str)
{
	if (!(*str = ft_strjoin_nf(*str, info->line, 1, info))
		|| !(ft_cut_room(info)))
	{
		(*str)[info->old_stop] = '\0';
		return (FALSE);
	}
	while (get_next_line(0, &info->line))
	{
		if (!(*str = ft_strjoin_nf(*str, info->line, 1, info)))
			return (FALSE);
		if (info->line[0] == '#')
		{
			if (!ft_strncmp(info->line,
				"#Here is the number of lines required: ", 39))
				info->lines_rqd = ft_atoi(info->line + 39);
			free(info->line);
		}
		else if (info->line[0] != '#')
			if (!(ft_cut_room(info)))
			{
				(*str)[info->old_stop] = '\0';
				return (BAD);
			}
	}
	return (TRUE);
}
