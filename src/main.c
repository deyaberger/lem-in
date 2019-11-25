/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:28:25 by ncoursol          #+#    #+#             */
/*   Updated: 2019/11/25 17:10:58 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

t_info	init_info(void)
{
	t_info	info;

	info.line = NULL;
	info.stop_str = 0;
	info.len_str = BUF;
	info.start = NULL;
	info.end = NULL;
	info.ant_nb = 0;
	info.room_nb = 0;
	info.size_tab = 0;
	info.link_nb = 0;
	info.lines_rqd = 0;
	info.max_paths = 0;
	info.coord = NULL;
	info.xmax = 0;
	info.ymax = 0;
	info.xmin = 2147483647;
	info.ymin = 2147483647;
	return (info);
}

t_room	*init_room(void)
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

BOOL	ft_error(t_info info, char *str, t_ways best, int mode)
{
	free(str);
	if (mode == 1)
		ft_clean_list(&info);
	if (mode == 2)
		ft_clean_steps(&best, 1);
	ft_clean_free(&info);
	ft_printf("ERROR\n");
	return (FALSE);
}

void	ft_visu(t_info info, char *str, t_ways best, int mode)
{
	if (VISU == 1 && mode == 1 && best.steps == NULL)
	{
		ft_printf("#%d %d %d ", info.room_nb, info.xmax, info.ymax);
		ft_printf("%d %d %d\n%s\n", info.xmin, info.ymin, info.link_nb, str);
	}
	if (VISU == 1 && mode == 2)
	{
		ft_printf("#F\n");
		ft_print_ways(&best);
		ft_printf("#0\n\n");
	}
}

int		main(void)
{
	t_info	info;
	t_room	*room;
	t_ways	best;
	char	*str;

	str = ft_memalloc(BUF);
	info = init_info();
	best.steps = NULL;
	if (!(room = init_room()) || !str)
		return (FALSE);
	info.first = room;
	if (ft_storage(&info, room, &str) == FALSE && ((info.room_nb = BAD) == BAD))
		return (ft_error(info, str, best, 0));
	if (ft_hashtab(&info, room, 0) == FALSE || ft_links(&info, &str) == FALSE)
		return (ft_error(info, str, best, 1));
	ft_visu(info, str, best, 1);
	best = ft_bfs(&info, room);
	if (best.steps == NULL)
		return (ft_error(info, str, best, 2));
	ft_visu(info, str, best, 2);
	ft_result(str, info, &best);
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
