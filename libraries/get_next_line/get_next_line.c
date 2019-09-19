/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:08:51 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/17 15:22:20 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	static t_f		*openfiles;
	t_f				*f;
	int				i;

	f = openfiles;
	while (!(i = 0) && f && f->d != fd)
		f = f->n;
	if (fd < 0 || (!f && (!(f = malloc(sizeof(*f))) ||
	((f->n = openfiles) && 0) || (f->d *= 0) || (f->d += fd) < 0 ||
	!(openfiles = f) || (f->i *= 0) || (f->j *= 0))) || (f->s *= 0))
		return (-1);
	while (!(f->k *= 0) && (f->i < f->j || (!(f->i *= 0) && (f->j = read(fd,
	f->r, BU_SI)) > 0)) && (f->s == 0 || f->r[f->i] != 10 || !(++f->i)))
	{
		if (i + BU_SI >= f->s && (f->k -= 1) && ((f->t = f->b) || 1)
		&& (f->b = (char *)malloc(sizeof(char) * (i + BU_SI + 1))))
			while (++(f->k) < i && (f->k) < f->s)
				free(((f->b[f->k] = f->t[f->k]) && (f->k + 1 < i) ? 0 : f->t));
		if (i + BU_SI >= f->s && ((!f->b && ((f->b = f->t) || 1))
		|| !(f->s = i + BU_SI + 1)))
			return (-1);
		while (f->i < f->j && f->r[f->i] != '\n')
			f->b[i++] = f->r[f->i++];
	}
	return ((i || f->j > 0) && (*line = f->b) && !(f->b[i] *= 0) ? 1 : f->j);
}
