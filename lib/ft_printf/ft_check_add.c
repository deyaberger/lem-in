/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 10:24:12 by ncoursol          #+#    #+#             */
/*   Updated: 2019/08/25 11:14:53 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_check_add(t_printf save, int *j, char c)
{
	if (*j == BUFF_SIZE && (*j = 0) == 0)
	{
		save.ret = save.ret + BUFF_SIZE;
		write(1, &save.buf, BUFF_SIZE);
	}
	save.buf[*j] = c;
	*j += 1;
	return (save);
}
