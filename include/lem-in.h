/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:31:12 by ncoursol          #+#    #+#             */
/*   Updated: 2019/11/20 12:39:23 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"

# define VISU 0
# define GOOD_PATH (1 << 1)
# define CLEAN (1 << 2)
# define REVERSE (1 << 3)
# define OUT (1 << 4)
# define BOOL int
# define BUF 200
# define TRUE 1
# define FALSE 0
# define ROOM_START 1
# define ROOM_END 2
# define ROOM_NORMAL 0
# define UNUSED 0
# define BACKWARD -1
# define FORWARD 1
# define CANCELED 0
# define INIT 0
# define FINISH 1
# define LENGTH 0
# define ANTS 1
# define STEPS 2
# define ANTS_SENT 3
# define ANT_ARRIVED 4
# define NONE -1
# define NEVER_FILLED -1
# define KEEP_SEARCHING 1
# define STOP 0
# define NOT_IN_QUEUE 0
# define IN_QUEUE 1

typedef struct		s_info
{
	char			*line;
	struct s_room	**tab;
	struct s_room	*first;
	struct s_room	*start;
	struct s_room	*end;
	int				**coord;
	int				stop_str;
	int				len_str;
	int				lines_rqd;
	int				ant_nb;
	int				max_paths;
	int				room_nb;
	int				link_nb;
	int				xmax;
	int				ymax;
//	int				fd;
}					t_info;

typedef struct		s_room
{
	char			*name;
	struct s_link	**link;
	struct s_room	*next;
	struct s_room	*mum;
	int				weight;
	int				ant_index;
	int				nbl;
	int				type; 	//start(1) | end(2) | rien(0)
	size_t			opti;
	size_t			in_q;
}					t_room;

typedef struct		s_link
{
	struct s_room	*dest;
	struct s_link	*rev;
	int8_t			status;
}					t_link;

typedef struct		s_ways
{
	struct s_room	***steps;
	int				**path_info;
	int				tot_max;
	int				min;
	int				nb_ways;
	int				tot_pl;
}					t_ways;

void				error_exit(int nb, char *str);
char				*ft_strjoin_nf(char *s1, char *s2, int a, t_info *info);
t_room				*init_room(void);
BOOL				ft_storage(t_info *t, t_room *r, int i, char **str);
int					ft_coll(t_info *info, char *name, int i, int s);
int					ft_hashage(char *name, int hash_size);
void				ft_hashtab(t_info *t, t_room *r);
BOOL				ft_links(t_info *t, char **str);
t_room				*ft_weight(t_info *t, t_room *r, t_room *queue);
void				ft_init_ways(t_ways **ways);
void				ft_clean_steps(t_ways *ways, int mode);
void				ft_clean_free(t_info *info);
t_ways				*ft_calc_steps(t_ways *ways, t_info *info, int j);
t_ways				*ft_steps(t_info *t, t_room *r, t_ways *comp);
t_ways				ft_bfs(t_info *t, t_room *r);
BOOL				ft_karp(t_info *t, t_room *r, t_ways *best, t_ways *comp);
void				ft_result(char *str, t_info info, t_ways *best);

#endif
