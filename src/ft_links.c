/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:16:59 by dberger           #+#    #+#             */
/*   Updated: 2019/10/18 14:39:01 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

t_link		*ft_create_ways(t_room *dest, t_info *t)
{
	t_link	*l;

	if (!(l = ft_memalloc(sizeof(t_link) * t->room_nb)))
		return (NULL);
	l->dest = dest;
	l->status = 0;
	return (l);
}

int8_t		ft_fill_links(int h1, int h2, t_info *t)
{
	unsigned int i;
	unsigned int j;
	t_room		*one;
	t_room		*two;

	i = 0;
	j = 0;
	one = t->tab[h1];
	two = t->tab[h2];
	while (one->ways[i] != NULL && i < t->room_nb && one->ways[i]->dest != two)
		i++;
	if (one->ways[i] == NULL)
	{
		one->ways[i] = ft_create_ways(two, t);
		one->nbl += 1;
	}	
	else if (one->ways[i]->dest == two)
		return (0);
	while (two->ways[j] != NULL && j < t->room_nb && two->ways[j]->dest != one)
		j++;
	if (two->ways[j] == NULL)
	{
		two->ways[j] = ft_create_ways(one, t);
		two->nbl += 1;
	}
	else if (two->ways[j]->dest == one)
		return (0);
	one->ways[i]->rev = two->ways[j];
	two->ways[j]->rev = one->ways[i];
	return (1);
}

int		ft_coal_links(int h, t_info *t, char *name, unsigned int s)
{
	while (t->tab[h] != NULL && ft_strcmp(t->tab[h]->name, name))
	{
		h++;
		if ((unsigned int)h == s)
			h = 0;
	}
	return (h);
}

int8_t		ft_calc_links(char *room1, char *room2, unsigned int s, t_info *t)
{
	int	h1;
	int	h2;

	h1 = 0;
	h2 = 0;
	h2 = ft_hashage(room2, s);
	h1 = ft_hashage(room1, s);
	if (t->tab[h1] == NULL || t->tab[h2] == NULL)
		return (0);
	h1 = ft_coal_links(h1, t, room1, s);
	h2 = ft_coal_links(h2, t, room2, s);
	if (t->tab[h1] == NULL || t->tab[h2] == NULL)
		return (0);
	ft_fill_links(h1, h2, t);
	free(t->line);
	return (1);
}

int8_t		ft_cut_room(t_info *t)
{
	char			*room1;
	char			*room2;
	unsigned int	s;

	s = 0;
	room1 = t->line;
	room2 = t->line;
	while (*room2 != '-' && *room2)
		room2++;
	room2++;
	while (room1[s] != '-' && room1[s])
		s++;
	room1[s] = '\0';
	s = t->room_nb * 10;
	if (!(ft_calc_links(room1, room2, s, t)))
		return (0);
	return (1);
}

int8_t		ft_links(t_info *t)
{
	if (!(ft_cut_room(t)))
		return (0);
	while (get_next_line(0, &t->line))
	{
		if (t->line[0] == '#' && t->line[1] == '#')
		{
			free(t->line);
			return (0);
		}
		if (t->line[0] != '#')
			if (!(ft_cut_room(t)))
				return (0);
	}
	return (1);
}
