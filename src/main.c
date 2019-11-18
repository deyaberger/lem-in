/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:28:25 by ncoursol          #+#    #+#             */
/*   Updated: 2019/11/18 16:55:27 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

t_info	init_info(void)
{
	t_info	info;

	info.line = NULL;
	info.stop_str = 0;
	info.len_str = BUF;
	info.ant_nb = 0;
	info.room_nb = 0;
	info.link_nb = 0;
	info.lines_rqd = 0;
	info.max_paths = 0;
	info.xmax = 0;
	info.ymax = 0;
	info.start = NULL;
	info.end = NULL;
	return (info);
}

t_room 	*init_room(void)
{
	t_room *room;

	if (!(room = ft_memalloc(sizeof(t_room*))))
		error_exit(2, "Can't malloc t_room");
	room->type = -1;
	room->link = NULL;
	room->mum = NULL;
	room->nbl = 0;
	room->ant_index = 0;
	room->stat = 0;
	room->weight = 0;
	room->opti = 0;
	room->name = NULL;
	room->next = NULL;
	return (room);
}

void  error_exit(int nb, char *str)
{
	ft_printf("Error [%d] : %s\n", nb, str);
	exit(nb);
}

void	ft_start_end(t_info *info)
{
	if (info->start->link[0] == NULL || info->end->link[0] == NULL)
		error_exit(6, "No paths possible between start and end");
	if (info->start->nbl <= info->end->nbl)
		info->max_paths = info->start->nbl;
	else
		info->max_paths = info->end->nbl;
}

void		ft_print_best(t_ways best)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < best.nb_ways && best.steps[i] != NULL)
	{
		ft_printf("\n");	
		while (best.steps[i][j] != NULL)
		{
			ft_printf("%s, ", best.steps[i][j]->name);
			j++;
		}
		ft_printf(" ==> LEN = %d, ANTS = %d, STEPS = %d\n", best.path_info[i][LENGTH], best.path_info[i][ANTS], best.path_info[i][STEPS]);
		j = 0;
		i++;
	}
	ft_printf("\nTOTAL WAYS = %d, TOTAL  STEPS = %d\n", best.nb_ways, best.tot_max);
}

int		main(void)
{
	t_info	info;
	t_room	*room;
	t_ways	best;
	int		i;
	char	*str;

	i = -1;
	str = ft_memalloc(BUF);
	info = init_info();
	room = init_room();
	info.first = room;
	if (!ft_storage(&info, room, i, &str))
		error_exit(1, "ft_storage has failed");
	ft_hashtab(&info, room);
	ft_links(&info, &str);
	ft_start_end(&info);
	best = ft_bfs(&info, room);
	ft_result(str, info, &best);
//	ft_print_best(best);
	ft_clean_steps(&best, 1);
	ft_clean_free(&info);
	return (FALSE);
}

/*
   __attribute__((destructor))
   void    end()
   {
   while(1);
   }*/
