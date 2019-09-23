/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 10:37:36 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/23 15:02:53 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int		storage(t_struct *t, t_lst *l)
{
	while (t->line[1] != '-' && t->line[0] != '#')
	{
		get_next_line(0, t->line);
		ft_printf("line : [%s]", t->line);
		free(t->line);
	}
	(void)l;
	return (0);
}
