/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:16:59 by dberger           #+#    #+#             */
/*   Updated: 2019/09/25 16:49:06 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int		ft_links(t_struct *t)
{
	int		i;
	int		h1;
	int		h2;
	char	*save;
	char	*save2;

	h1 = 0;
	h2 = 0;
	i = 0;
	save = t->line;
	while (*save == '-' && *save)
		save++;
	save2 = save;
	while (*save != '-' && *save)
	{
		save++;
		i++;
	}
	while (*save == '-' && *save)
		save++;
	if (ft_strchr(save, '-'))
	{
		while (save[h1] != '-' && save[h1])
			h1++;
		save[h1] = '\0';
	}
	h2 = ft_hashage(save, t->room_nb * 10);
	save = save2;
	save[i] = '\0';
	h1 = ft_hashage(save, t->room_nb * 10); 
	ft_printf("h1 = %d, h2 = %d\n", h1, h2);
	return (1);
}
