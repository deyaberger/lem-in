/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:16:59 by dberger           #+#    #+#             */
/*   Updated: 2019/09/26 19:14:11 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int		ft_fill_links(int h1, int h2, t_struct *t)
{
	unsigned int i;

	i = 0;
	while (i < t->room_nb && t->tab[h1]->link[i] != -1
			&& t->tab[h1]->link[i] != h2)
		i++;
	if (t->tab[h1]->link[i] == h2)
		return (0);
	t->tab[h1]->link[i] = h2;
	if (i < t->room_nb - 1)
		t->tab[h1]->link[i + 1] = -1;
	i = 0;
	while (i < t->room_nb && t->tab[h2]->link[i] != -1
			&& t->tab[h2]->link[i] != h1)
		i++;
	if (t->tab[h2]->link[i] == h1)
		return (0);
	t->tab[h2]->link[i] = h1;
	if (i < t->room_nb - 1)
		t->tab[h2]->link[i + 1] = -1;
	return (1);
}

int		ft_coal_links(int h, t_struct *t, char *name, unsigned int s)
{
	while (t->tab[h] != NULL && ft_strcmp(t->tab[h]->name, name))
	{
		h++;
		if ((unsigned int)h == s)
			h = 0;
	}
	return (h);
}

int		ft_calc_links(char *room1, char *room2, unsigned int s, t_struct *t)
{
	int				h1;
	int				h2;

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

int		ft_cut_room(t_struct *t)
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

int		ft_links(t_struct *t)
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
