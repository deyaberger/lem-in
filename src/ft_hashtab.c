/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:17:46 by dberger           #+#    #+#             */
/*   Updated: 2019/10/03 19:30:28 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

unsigned int	ft_hashage(char *name, int hash_size)
{
	size_t			i;
	unsigned int	hash;

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

void			ft_init_tab(t_struct *t, unsigned int s)
{
	unsigned int i;

	i = 0;
	while (i < s)
	{
		t->tab[i] = NULL;
		i++;
	}
}

int				ft_init_links_tab(t_struct *t, t_room *r, int i)
{
	unsigned int		j;

	j = 0;
	t->tab[i] = r;
	if (!(r->ways = malloc(sizeof(r->ways) * t->room_nb)))
		return (0);
	while (j < t->room_nb)
	{
		r->ways[j] = NULL;
		j++;
	}
	if (r->type == 1)
		t->start = r;
	else if (r->type == 2)
		t->end = r;
	return (1);
}

int				ft_coal(t_struct *t, t_room *r, int i, int s)
{
	while (i < s && t->tab[i] != NULL && ft_strcmp(r->name, t->tab[i]->name))
	{
		i++;
		if (i == s)
			i = 0;
	}
	if (t->tab[i] == NULL)
	{
		if (!(ft_init_links_tab(t, r, i)))
			return (0);
	}
	else if (!(ft_strcmp(r->name, t->tab[i]->name)))
		return (0);
	return (1);
}

int				ft_hashtab(t_struct *t, t_room *r)
{
	unsigned int	i;
	unsigned int	s;

	s = t->room_nb * 10;
	if (!(t->tab = malloc(sizeof(t->tab) * s)))
		return (0);
	ft_init_tab(t, s);
	r = t->first;
	while (r)
	{
		i = ft_hashage(r->name, s);
		if (i < s && t->tab[i] == NULL)
		{
			if (!(ft_init_links_tab(t, r, i)))
				return (0);
		}
		else
		{
			if (!(ft_coal(t, r, i, s)))
				return (0);
		}
		r = r->next;
	}
	return (1);
}
