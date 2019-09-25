/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:16:59 by dberger           #+#    #+#             */
/*   Updated: 2019/09/25 15:42:30 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int		ft_links(t_struct *t)
{
	int		i;
	int		h;

	i = 0;
	ft_printf("t->line =%s\n", t->line);
	while (t->line[i] != '-')
		i++;
	ft_printf("line[i]=%c\n", t->line[i]);
	return (1);
}
