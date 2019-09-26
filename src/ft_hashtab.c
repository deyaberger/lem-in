/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:17:46 by dberger           #+#    #+#             */
/*   Updated: 2019/09/26 17:56:25 by dberger          ###   ########.fr       */
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
	t->tab[i] = r;
	if (!(t->tab[i]->link = (int*)malloc(sizeof(int) * t->room_nb + 1)))
		return (0);
	ft_bzero(t->tab[i]->link, t->room_nb);
	t->tab[i]->link[0] = -1;
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
	t->tab = malloc(sizeof(t->tab) * s);
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
