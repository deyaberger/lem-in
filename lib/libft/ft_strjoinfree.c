/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:45:14 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/16 13:45:23 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoinfree(const char *s1, const char *s2, int i)
{
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	if (!(dest = ft_strjoin(s1, s2)))
		return (NULL);
	if (i == 1 || i == 3)
		free((char *)s1);
	if (i == 2 || i == 3)
		free((char *)s2);
	return (dest);
}
