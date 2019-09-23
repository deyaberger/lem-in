/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:54:24 by dberger           #+#    #+#             */
/*   Updated: 2019/09/17 15:04:46 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char		*s2;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	s2 = (char *)s;
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
	{
		return (NULL);
	}
	while (i < len)
	{
		s2[i] = s[start + i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
