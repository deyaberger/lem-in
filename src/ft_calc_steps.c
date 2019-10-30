/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_steps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:05:16 by dberger           #+#    #+#             */
/*   Updated: 2019/10/30 17:15:05 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

size_t	ft_calc_ants(t_info *info, t_ways **ways, size_t i)
{
	size_t len;
	size_t ants;
	size_t a;
	size_t tpl;

	ants = info->ant_nb;
	tpl = (*ways)->tot_pl;
	len = (*ways)->path_info[i][LENGTH];
	a = ((ants + tpl - ((*ways)->nb_ways * len)) / ((*ways)->nb_ways));
	(*ways)->path_info[i][ANTS] = a;
	return (a);
}

void	ft_min_max(t_ways **ways, size_t i)
{
	size_t steps;

	steps = (*ways)->path_info[i][STEPS];
	if (steps > (*ways)->tot_max)
		(*ways)->tot_max = steps;
	if (steps < (*ways)->min)
		(*ways)->min = steps;
}

void	ft_one_path_steps(t_ways **ways, size_t i, size_t a)
{
	size_t len;
	size_t steps;

	len = (*ways)->path_info[i][LENGTH];
	steps = len + a - 1;
	(*ways)->path_info[i][STEPS] = steps;
}

void	ft_left_over(t_info *info, t_ways **ways, int nb)
{
	size_t i;
	size_t a;
	size_t rest;
	size_t left;

	i = 0;
	a = 0;
	rest = 1;
	left = info->ant_nb - nb;
	while (left > 0)
	{
		i = 0;
		while (i < (*ways)->nb_ways
				&& (*ways)->path_info[i][STEPS] != (*ways)->min)
			i++;
		(*ways)->path_info[i][ANTS] += rest;
		a = (*ways)->path_info[i][ANTS];
		ft_one_path_steps(ways, i, a);
		ft_min_max(ways, i);
		left--;
		rest++;
	}
}

t_ways	*ft_calc_steps(t_ways *ways, t_info *info, size_t j)
{
	size_t	i;
	size_t	nb;
	size_t	a;

	i = 0;
	nb = 0;
	a = 0;
	ways->nb_ways = j + 1;
	while (i < ways->nb_ways)
	{
		a = ft_calc_ants(info, &ways, i);
		nb = nb + a;
		ft_one_path_steps(&ways, i, a);
		ft_min_max(&ways, i);
		i++;
	}
	if ((int)nb < info->ant_nb)
		ft_left_over(info, &ways, nb);
	return (ways);
}
