/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:31:12 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/23 13:43:04 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

//# include "../libraries/ft_printf/ft_printf.h"
//# include "../libraries/get_next_line/get_next_line.h"
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct		s_struct
{
	int				ant_nb;
	int				room_nb;
	int				pipe_nb;
}					t_struct;

typedef struct		s_lst
{
	char			*name;
	int				type; 	//start(1) | end(2) | rien(0)
	int				*link;	//liaisons
	struct s_lst	*next;
}					t_lst;

#endif
