/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:16:59 by dberger           #+#    #+#             */
/*   Updated: 2019/09/25 18:00:59 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int		ft_links(t_struct *t)
{
	unsigned int	i;
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
	if (t->tab[h1] == NULL || t->tab[h2] == NULL)
			return (0);
	ft_printf("h1 = %d, h2 = %d\n", h1, h2);
	ft_printf("t->tab[%d]->name = %s, type = %d\nt->tab[%d]->name = %s, type = %d\n", h1, t->tab[h1]->name, t->tab[h1]->type, h2, t->tab[h2]->name, t->tab[h2]->type);
	i = 0;
	while (t->tab[h1]->link[i] != -1  && i < t->room_nb)
		i++;
	t->tab[h1]->link[i] = h2;
	if (i < t->room_nb - 1)
		t->tab[h1]->link[i + 1] = -1;
	i = 0;
	while (t->tab[h2]->link[i] != -1  && i < t->room_nb)
		i++;
	t->tab[h2]->link[i] = h1;
	if (i < t->room_nb - 1)
		t->tab[h2]->link[i + 1] = -1;
	return (1);
}
