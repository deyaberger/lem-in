/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 10:24:24 by ncoursol          #+#    #+#             */
/*   Updated: 2019/08/22 10:24:26 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_check_char(char *str, int i, int mode)
{
	if (mode == 1)
	{
		if (str[i] != 'd' && str[i] != 'i' && str[i] != 'o' && str[i] != 'u'
			&& str[i] != 'x' && str[i] != 'X' && str[i] != 'f' && str[i] != 'c'
			&& str[i] != 's' && str[i] != 'p' && str[i] != '%' && str[i] != 'b'
			&& str[i] != 'F')
			return (0);
	}
	if (mode == 2)
	{
		if (str[i] != ' ' && str[i] != '+' && str[i] != '-' && str[i] != '#'
			&& str[i] != '.' && str[i] != '0' && (str[i] < '0' || str[i] > '9')
			&& str[i] != 'h' && str[i] != 'l' && str[i] != 'L'
			&& str[i] != 'z' && str[i] != 'j')
			return (0);
	}
	if (mode == 3)
	{
		if (str[i] && (str[i] == ' ' || str[i] == 'h'
			|| str[i] == 'l' || str[i] == 'L' || str[i] == 'z'
			|| str[i] == 'j'))
			return (0);
	}
	return (1);
}
