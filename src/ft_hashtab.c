/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:17:46 by dberger           #+#    #+#             */
/*   Updated: 2019/09/25 19:38:17 by dberger          ###   ########.fr       */
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

void		ft_init_tab(t_struct *t)
{
	unsigned int i;

	i = 0;
	while (i < t->room_nb * 10)
	{
		t->tab[i] = NULL;
		i++;
	}
}

int			ft_hashtab(t_struct *t, t_room *r)
{
	unsigned int 	i;
	
	t->tab = malloc(sizeof(t->tab) * t->room_nb * 10);
	ft_init_tab(t);
	r = t->first;
	while (r)
	{
		i = ft_hashage(r->name, (t->room_nb * 10));
		if (t->tab[i] == NULL && i < (t->room_nb * 10))
		{
			t->tab[i] = r;
			if (!(t->tab[i]->link = (int*)malloc(sizeof(int) * t->room_nb + 1)))
				return (0);
			ft_bzero(t->tab[i]->link, t->room_nb);
			t->tab[i]->link[0] = -1;
		}
		else
		{
			while (i < (t->room_nb * 10) && t->tab[i] != NULL && ft_strcmp(r->name, t->tab[i]->name))
			{
				i++;
				if (i == (t->room_nb * 10))
					i = 0;
			}

			if (t->tab[i] == NULL)
				t->tab[i] = r;
			else if (!(ft_strcmp(r->name, t->tab[i]->name)))
				return (0);
		}
		r = r->next;
	}
	return (1);
}
