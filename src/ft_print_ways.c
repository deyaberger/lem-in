/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ways.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:30:21 by dberger           #+#    #+#             */
/*   Updated: 2019/12/06 15:28:52 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	ft_lines_rqd(t_info info, int total)
{
	char	*str;

	if (info.option == 1)
	{
		str = "#Here is the number of lines required: ";
		if (info.lines_rqd != 0)
			ft_printf("\n%s%d\n", str, info.lines_rqd);
		else
			ft_printf("\n%sNOT SPECIFIED\n", str);
		ft_printf("#Here is the number of lines actually used: %d\n", total);
	}
}

BOOL	ft_s_with_e(t_info info)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (info.start->link[j] && k == 0)
	{
		if (info.start->link[j]->dest == info.end)
			k = 1;
		j++;
	}
	return (k == 1 ? TRUE : FALSE);
}

BOOL	ft_particular(t_ways *best, t_info info)
{
	int	j;

	j = 0;
	if (ft_s_with_e(info) == TRUE
		|| (best->nb_ways == 1 && best->path_info[0][LENGTH] == 1))
	{
		j++;
		while (j <= info.ant_nb)
		{
			if (j == info.ant_nb)
				ft_printf("L%d-%s", j, info.end->name);
			else
				ft_printf("L%d-%s ", j, info.end->name);
			j++;
		}
		ft_printf("\n");
		ft_lines_rqd(info, 1);
		return (FALSE);
	}
	return (TRUE);
}

void	ft_print_ways(t_ways *ways)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ways->nb_ways && ways->steps[i] != NULL)
	{
		while (ways->steps[i][j] != NULL)
		{
			ft_printf("-%s", ways->steps[i][j]->name);
			if (j >= ways->path_info[i][LENGTH] - 1)
				ft_printf("\n");
			j++;
		}
		j = 0;
		i++;
	}
}
