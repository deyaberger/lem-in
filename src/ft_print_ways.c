/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ways.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:30:21 by dberger           #+#    #+#             */
/*   Updated: 2019/11/26 15:44:23 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void	ft_lines_rqd(t_info info, int total)
{
	char	*str;

	str = "#Here is the number of lines required: ";
	if (info.lines_rqd != 0)
		ft_printf("\n%s%d\n", str, info.lines_rqd);
	else
		ft_printf("\n%sNOT SPECIFIED\n", str);
	ft_printf("#Here is the number of lines actually used: %d\n", total);
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
