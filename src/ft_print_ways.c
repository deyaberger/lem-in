/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ways.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:30:21 by dberger           #+#    #+#             */
/*   Updated: 2019/11/21 17:37:13 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void		ft_print_ways(t_ways *ways)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ways->nb_ways && ways->steps[i] != NULL)
	{
		ft_printf("*");
		while (ways->steps[i][j] != NULL)
		{
			ft_printf("%s", ways->steps[i][j]->name);
			if (j < ways->path_info[i][LENGTH] - 1)
				ft_printf("-");
			else
				ft_printf("\n");
			j++;
		}
		j = 0;
		i++;
	}
}
