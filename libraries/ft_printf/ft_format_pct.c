/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_pct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:30:20 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/17 15:30:21 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf		ft_format_pct(t_printf save, int *j)
{
	int		w;

	w = 0;
	if (save.width > 0)
	{
		w = save.width - 1;
		if (save.flags & F_MINUS)
			save = ft_check_add(save, j, '%');
		while (w > 0)
		{
			if (save.flags & F_ZERO && !(save.flags & F_MINUS))
				save = ft_check_add(save, j, '0');
			else
				save = ft_check_add(save, j, ' ');
			w--;
		}
		if (!(save.flags & F_MINUS))
			save = ft_check_add(save, j, '%');
		return (save);
	}
	return (ft_check_add(save, j, '%'));
}
