/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:28:25 by ncoursol          #+#    #+#             */
/*   Updated: 2019/11/21 16:24:16 by dberger          ###   ########.fr       */
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
	info.xmin = 0;
	info.ymin = 0;
	info.start = NULL;
	info.coord = NULL;
	info.end = NULL;
	return (info);
}

t_room 	*init_room(void)
{
	t_room *room;

	if (!(room = ft_memalloc(sizeof(t_room*))))
		return (NULL);
	room->link = NULL;
	room->mum = NULL;
	room->nbl = 0;
	room->ant_index = 0;
	room->in_q = 0;
	room->weight = 0;
	room->opti = 0;
	room->name = NULL;
	room->next = NULL;
	return (room);
}

BOOL	ft_start_end(t_info *info)
{
	if (info->start->link[0] == NULL || info->end->link[0] == NULL)
		return (FALSE);
	if (info->start->nbl <= info->end->nbl)
		info->max_paths = info->start->nbl;
	else
		info->max_paths = info->end->nbl;
	return (TRUE);
}

////// just pour les test:

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
/////////

void	ft_error(t_info info, char *str)
{
	free(str);
	ft_clean_free(&info);
	ft_printf("ERROR\n");
}

int		main(void)
{
	t_info	info;
	t_room	*room;
	t_ways	best;
	char	*str;

	if (!(str = ft_memalloc(BUF)))
		return (FALSE);
	info = init_info();
	if (!(room = init_room()))
		return (FALSE);
	info.first = room;
	if (ft_storage(&info, room, &str) == FALSE)
	{
		ft_error(info, str);
		if (room)
			free(room);
		return (FALSE);
	}
	if (ft_hashtab(&info, room) == FALSE)
	{
		ft_error(info, str);
		return (FALSE);
	}
	if (ft_links(&info, &str) == FALSE)
	{
		ft_error(info, str);
		return (FALSE);
	}	
	if (ft_start_end(&info) == FALSE)
	{
		ft_error(info, str);
		return (FALSE);
	}	
	best = ft_bfs(&info, room);
	if (best.steps == NULL)
	{
		ft_clean_steps(&best, 1);
		ft_error(info, str);
		return (FALSE);
	}	
	ft_result(str, info, &best);
//	ft_print_best(best);
	free(str);
	ft_clean_steps(&best, 1);
	ft_clean_free(&info);
	return (TRUE);
}

/*
   __attribute__((destructor))
   void    end()
   {
   while(1);
   }*/
