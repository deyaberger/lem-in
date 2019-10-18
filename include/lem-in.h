/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:31:12 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/18 14:41:22 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"

typedef struct		s_info
{
	char		*line;
	struct s_room	**tab;
	struct s_room	*first;
	struct s_room	*start;
	struct s_room	*end;
	int		**coord;
	int		ant_nb;
	int		max_paths;
	unsigned int	room_nb;
	unsigned int	link_nb;
	int		xmax;
	int		ymax;
}			t_info;

typedef struct		s_room
{
	char		*name;
	struct s_link	**ways;
	struct s_room	*next;
	struct s_room	*mum;
	int		type; 	//start(1) | end(2) | rien(0)
	int		weight;
	int		opti;
	int		q;
	int		used;
	int		nbl;
}			t_room;

typedef struct		s_link
{
	struct s_room	*dest;
	struct s_link	*rev;
	int		status;	
}			t_link;

typedef struct		s_ways
{
	struct s_room	***steps;
	int		total;
	int		nb_ways;
}			t_ways;

int8_t			ft_storage(t_info *t, t_room *r, int i);
t_room			*init_room(t_room *r);
unsigned int		ft_hashage(char *name, int hash_size);
int8_t			ft_hashtab(t_info *t, t_room *r);
int8_t			ft_links(t_info *t);
t_room			*ft_weight(t_info *t, t_room *r, t_room *queue);
int8_t			ft_bfs(t_info *t, t_room *r);
int8_t			ft_steps(t_info *t, t_room *r, t_ways *comp);
int8_t			ft_karp(t_info *t, t_room *r, t_ways *best, t_ways *comp);

#endif
