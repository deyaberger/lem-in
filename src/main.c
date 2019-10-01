/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:28:25 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/01 15:21:41 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void			free_all(t_struct *t, t_room **r, int mode)
{
	t_room	*next_one;

	while (*r)
	{
		next_one = (*r)->next;
		if ((*r)->name)
			free((*r)->name);
		free(*r);
		*r = next_one;
	}
	*r = NULL;
	if (t->line)
		free(t->line);
	if (mode == 1)
		ft_printf("ERROR\n");
}

void			init_var(t_struct *t)
{
	t->line = NULL;
	t->ant_nb = 0;
	t->room_nb = 0;
	t->pipe_nb = 0;
	t->xmax = 0;
	t->ymax = 0;
	t->start = -1;
	t->end = -1;
	t->max_paths = -1;
}

t_room			*init_room(t_room *r)
{
	if (!(r = (t_room*)malloc(sizeof(*r))))
		r->type = -2;
	r->type = -1;
	r->name = NULL;
	r->next = NULL;
	r->ant = 0;
	r->nbl = 0;
	return (r);
}

int		main(void)
{
	t_struct	t;
	t_room		*r = NULL;
	int			i;

	i = -1;
	init_var(&t);
	r = init_room(r);
	if (r->type == -2)
	{
		free_all(&t, &r, 1);
		return (-1);
	}
	t.first = r;
	if (!ft_storage(&t, r, i))
	{
		free_all(&t, &r, 1);
		return (-1);
	}
	ft_hashtab(&t, r);
	ft_links(&t);
/*	i = 0;
	int j;
	j = 0;
	while ((unsigned int)i < t.room_nb * 10)
	{
		if (t.tab[i] != NULL)
		{
			ft_printf("%s-tab[%d]: nbl = %d, links = [", t.tab[i]->name, i, t.tab[i]->nbl);
			while (t.tab[i]->link[j] != -1)
			{
				ft_printf("%d,", t.tab[i]->link[j]);
				j++;
			}
			j = 0;
			ft_printf("]\n");
		}
		i++;
	}*/
	free_all(&t, &r, 0);
	return (0);
}
/*
   __attribute__((destructor))
   void    end()
   {
   while(1);
   }*/
