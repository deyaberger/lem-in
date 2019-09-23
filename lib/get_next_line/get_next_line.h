/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:02:30 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/17 15:21:47 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# define BU_SI 32

typedef struct	s_f
{
	int				d;
	int				s;
	char			*b;
	char			*t;
	char			r[BU_SI];
	int				i;
	int				j;
	int				k;
	struct s_f		*n;
}				t_f;

int				get_next_line(const int fd, char **line);

#endif
