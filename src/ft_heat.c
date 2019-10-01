/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 14:20:15 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/01 17:57:39 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int		ft_init_hm(t_room *h)
{
	int		i;

	i = 0;
	if (!(h->hm = (int*)malloc(sizeof(int) * (h->nbl - 1))))
		return (0);
	while (i < (h->nbl - 1))
	{
		h->hm[i] = 0;
		i++;
	}
	return (1);
}

int		add()
{




	return (1);
}

int		heat(t_struct *t, t_room *h)
{
	int		j;

	j = 0;
	while (1)
	{
		
	
	
	
	
	
	
	
	
	
	
	
	}
	return (1);
}

int		ft_heat(t_struct *t)
{
	t_room	*h;

	h = t->tab[t->end];
	ft_init_hm(h);
	h->hm[0] = 1;
	ft_printf("%s[0] : [%d]\n", h->name, h->hm[0]);
	if (!heat(t, h, i))
		return (0);
	return (1);
}
