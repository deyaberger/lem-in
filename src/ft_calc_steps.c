/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_steps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:05:16 by dberger           #+#    #+#             */
/*   Updated: 2019/11/13 14:41:23 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

long	ft_calc_ants(t_info *info, t_ways **ways, int i)
{
	long len;
	long ants;
	long a;
	long tpl;
	long nb_w;

	ants = info->ant_nb;
	tpl = (*ways)->tot_pl;
	len = (*ways)->path_info[i][LENGTH];
	nb_w = (*ways)->nb_ways;
	a = ((ants + tpl - (nb_w * len)) / nb_w);
	(*ways)->path_info[i][ANTS] = a;
	return (a);
}

void	ft_min_max(t_ways **ways, int i)
{
	int steps;

	steps = (*ways)->path_info[i][STEPS];
	if (steps > (*ways)->tot_max)
		(*ways)->tot_max = steps;
	if (steps < (*ways)->min)
		(*ways)->min = steps;
}

void	ft_one_path_steps(t_ways **ways, int i, int a)
{
	int len;
	int steps;

	len = (*ways)->path_info[i][LENGTH];
	steps = len + a - 1;
	(*ways)->path_info[i][STEPS] = steps;
}

void	ft_left_over(t_info *info, t_ways **ways, int nb)
{
	int i;
	int a;
	int left;

	i = 0;
	a = 0;
	left = info->ant_nb - nb;
	while (left > 0)
	{
		i = 0;
		while (i < (*ways)->nb_ways
				&& (*ways)->path_info[i][STEPS] != (*ways)->min)
			i++;
		(*ways)->path_info[i][ANTS] += 1;
		a = (*ways)->path_info[i][ANTS];
		ft_one_path_steps(ways, i, a);
		ft_min_max(ways, i);
		left--;
	}
}

t_ways	*ft_calc_steps(t_ways *ways, t_info *info, int j)
{
	int	i;
	int	nb;
	int	a;

	i = 0;
	nb = 0;
	a = 0;
	ways->nb_ways = j + 1;
	while (i < ways->nb_ways)
	{
		a = ft_calc_ants(info, &ways, i);
		if (a < 0)
		{
			ways->tot_max = -1;
			return (ways);
		}
		nb = nb + a;
		ft_one_path_steps(&ways, i, a);
		ft_min_max(&ways, i);
		i++;
	}
	if (nb < info->ant_nb)
		ft_left_over(info, &ways, nb);
	return (ways);
}
