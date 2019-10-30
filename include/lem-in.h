/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:31:12 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/30 15:43:13 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"

#define BOOL int
#define TRUE 1
#define FALSE 0
#define NO_MORE_STEPS 0
#define ROOM_START 1
#define ROOM_END 2
#define ROOM_NORMAL 0
#define GOOD_PATH 1
#define CLEAN 2
#define REVERSE 3
#define CONTINUE_AFTER_REVERSE 4
#define	UNUSED 0
#define	BACKWARD -1
#define	FORWARD 1
#define	CANCELED 0
#define	INIT 0
#define	FINISH 1
#define	LENGTH 0
#define	ANTS 1
#define	STEPS 2
#define	NONE -1

typedef struct		s_info
{
	char		*line;
	struct s_room	**tab;
	struct s_room	*first;
	struct s_room	*start;
	struct s_room	*end;
	int		**coord;
	int		ant_nb;
	size_t		max_paths;
	size_t		room_nb;
	size_t		link_nb;
	int		xmax;
	int		ymax;
}			t_info;

typedef struct		s_room
{
	char		*name;
	struct s_link	**link;
	struct s_room	*next;
	struct s_room	*mum;
	size_t		weight;
	size_t		nbl;
	int		type; 	//start(1) | end(2) | rien(0)
	int		opti;
	int		q;
	int		used;
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
	size_t		tot_max;
	size_t		min;
	size_t		nb_ways;
	size_t		**path_info;
	size_t		tot_pl;
}			t_ways;

void			error_exit(int nb, char *str);
t_room			*init_room(void);
BOOL			ft_storage(t_info *t, t_room *r, int i);
size_t			ft_coll(t_info *info, char *name, size_t i, size_t s);
size_t			ft_hashage(char *name, int hash_size);
void			ft_hashtab(t_info *t, t_room *r);
BOOL			ft_links(t_info *t);
t_room			*ft_weight(t_info *t, t_room *r, t_room *queue);
void			ft_clean_steps(t_ways *ways, int mode);
t_ways			*ft_calc_steps(t_ways *ways, t_info *info, size_t j);
void			ft_steps(t_info *t, t_room *r, t_ways *comp);
BOOL			ft_bfs(t_info *t, t_room *r);
void			ft_karp(t_info *t, t_room *r, t_ways *best, t_ways *comp);

#endif
