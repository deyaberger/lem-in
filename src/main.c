/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:28:25 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/23 14:39:46 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void			error_output()
{
	//free all
	ft_printf("ERROR\n");
}

t_struct		init_var(t_struct t)
{
	t.line = NULL;
	t.ant_nb = 0;
	t.room_nb = 0;
	t.pipe_nb = 0;
	return (t);
}

t_lst			init_lst(t_lst *l)
{
	if (!(l = (t_lst*)malloc(sizeof(*l))))
	{
		l->type = -1;
		return (l);
	}
	l->type = 0;
	l->next = NULL;
	return (l);
}

int		main(void)
{
	t_struct	t;
	t_lst		*l;

	t = init_var(t);
	if (l->type == -1)
		return (1);
	l = init_lst(l); //free
	storage(&t, l);
//	algo(t, l);
	return (0);
}
