/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:17:46 by dberger           #+#    #+#             */
/*   Updated: 2019/09/24 19:30:25 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

unsigned int		ft_hashage(char *name, int hash_size)
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

int			ft_hashtab(t_struct *t, t_room *r)
{
	unsigned int 	i;
	t_room	**tab;
	
	tab = malloc(sizeof(tab) * t->room_nb * 10);
	r = t->first;
	i = 79;
	tab[i] = r; 
	ft_printf("tab[%d]->name=%s\n", i, tab[i]->name);
/*	while (r)
	{
		i = ft_hashage(r->name, (t->room_nb * 10));
		ft_printf("pour name = '%s', index = %d\n", r->name, i);
		if (t->hash[i] == NULL)
			t->hash[i] = r;
		else
		{
			while (t->hash[i] && ft_strcmp(r->name, t->hash[i]->name))
				i++;
			if (t->hash[i] == NULL)
				t->hash[i] = r;
			else if (!(ft_strcmp(r->name, t->hash[i]->name)))
				return (0);
		}
		r = r->next;
	}*/
	return (1);
}
