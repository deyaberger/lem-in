/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:28:25 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/23 20:55:27 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void			error_output()
{
	//free all
	ft_printf("ERROR\n");
}

void			init_var(t_struct *t)
{
	t->line = NULL;
	t->ant_nb = 0;
	t->room_nb = 0;
	t->pipe_nb = 0;
}

t_room			*init_room(t_room *r)
{
	if (!(r = (t_room*)malloc(sizeof(*r))))
		r->type = -2;
	r->type = -1;
	r->name = NULL;
	r->next = NULL;
	return (r);
}

int		main(void)
{
	t_struct	t;
	t_room		*r = NULL;

	init_var(&t);
	r = init_room(r); //free
	if (r->type == -2)
		return (1);
	t.first = r;
	ft_storage(&t, r);
//	algo(t, l);
	return (0);
}
