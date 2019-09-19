/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:28:25 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/19 19:00:34 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/get_next_line/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int		init_var(t_struct t)
{
	t.ant_nb = 0;
	t.room_nb = 0;
	t.pipe_nb = 0;
	return (t);
}

int		main(void)
{
	char		*line;
	t_struct	t;

	init_var(t);
	get_next_line(0, &line);
	
	free(line);
	return (0);
}
