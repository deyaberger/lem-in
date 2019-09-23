/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:28:25 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/23 15:12:00 by ncoursol         ###   ########.fr       */
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

void			init_lst(t_lst *l)
{
	if (!(l = (t_lst*)malloc(sizeof(*l))))
		l->type = -1;
	l->type = 0;
	l->next = NULL;
}

int		main(void)
{
	t_struct	t;
	t_lst		l;

	init_var(&t);
	init_lst(&l); //free
	if (l.type == -1)
		return (1);
	ft_storage(&t, &l);
//	algo(t, l);
	return (0);
}
