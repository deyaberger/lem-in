/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:31:12 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/24 19:33:39 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"

typedef struct		s_struct
{
	char			*line;
	int				ant_nb;
	int				room_nb;
	int				pipe_nb;
	int				xmax;
	int				ymax;
	struct s_room	*first;
}					t_struct;

typedef struct		s_room
{
	char			*name;
	int				type; 	//start(1) | end(2) | rien(0)
	int				*link;	//liaisons
	struct s_room	*next;
}					t_room;

int					ft_storage(t_struct *t, t_room *r, int i);
t_room				*init_room(t_room *r);
int					ft_hashtab(t_struct *t, t_room *r);

#endif
