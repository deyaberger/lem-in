/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_karp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:00:23 by dberger           #+#    #+#             */
/*   Updated: 2019/10/18 14:27:43 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void	ft_clean_best(t_ways *best)
{
	int j;
	int k;

	j = 0;
	k = 0;
	while (j <= best->nb_ways)
	{
		while (best->steps[j][k] != NULL)
		{
			best->steps[j][k] = NULL;
			k++;
		}
		k = 0;
		j++;
	}

}

void	ft_new_best(t_struct *t, t_ways *best, t_ways *comp)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (comp->steps[j] && j <= comp->nb_ways)
	{
		if (j > best->nb_ways)
		{
			best->steps[j] = ft_memalloc(sizeof(t_room) * t->end->weight);
			best->steps[j + 1] = NULL;
		}
		while (comp->steps[j][k])
		{
			best->steps[j][k] = comp->steps[j][k];
			comp->steps[j][k] = NULL;
			k++;
		}
		comp->steps[j] = NULL;
		best->nb_ways = j;
		k = 0;
		j++;
	}
	comp->nb_ways = 0;


}

void	ft_link_status(t_room *r)
{
	t_link	*link;
	int	i;

	i = 0;
	link = NULL;
	while (r->ways[i]->dest != r->mum)
		i++;
	link = r->ways[i];
	if (link->status == 0 && link->rev->status == 0)
	{
		link->status = -1;
		link->rev->status = 1;
	}
	else if (link->status == 1 && link->rev->status == -1)
	{
		link->status = 0;
		link->rev->status = 0;
	}
}

void	ft_karp(t_struct *t, t_room *r, t_ways *best, t_ways *comp)
{
	r = t->end;
	while (r != t->start)
	{
		ft_link_status(r);
		r = r->mum;
	}
	if (best->steps[0] == NULL)
		ft_steps(t, r, best);
	else
		ft_steps(t, r, comp);
	if (comp->steps[0] != NULL  && comp->total < best->total)
	{
		ft_clean_best(best);
		ft_new_best(t, best, comp);
	}
}
