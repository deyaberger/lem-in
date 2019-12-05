  
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:28:25 by ncoursol          #+#    #+#             */
/*   Updated: 2019/11/27 16:42:18 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

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
	if (mode == FAIL_HASH && info.link_nb == 0)
		ft_clean_list(&info, info.first);
	if (mode == FAIL_HASH && info.link_nb != 0 && info.max_paths != IMPOSSIBLE)
		free(info.line);
	if (mode == FAIL_BFS)
		ft_clean_steps(&best, 1);
	ft_clean_free(&info);
	ft_printf("ERROR\n");
	return (FALSE);
}

BOOL	ft_visu(t_info *info, char *str, t_ways best, int mode)
{
	if ((info->start->link[0] == NULL || info->end->link[0] == NULL)
		&& (info->max_paths = IMPOSSIBLE) == IMPOSSIBLE)
		return (FALSE);
	info->max_paths = (info->start->nbl <= info->end->nbl ?
						info->start->nbl : info->end->nbl);
	if (VISU == 1 && mode == 1 && best.steps == NULL)
	{
		info->link_nb = info->link_nb / 2;
		ft_printf("#%d %d %d ", info->room_nb, info->xmax, info->ymax);
		ft_printf("%d %d %d\n%s\n", info->xmin, info->ymin, info->link_nb, str);
	}
	if (VISU == 1 && mode == 2)
	{
		ft_printf("#F\n");
		ft_print_ways(&best);
		ft_printf("#0\n\n");
	}
	return (TRUE);
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
		return (ft_error(info, str, best, FAIL_STOR));
	if (ft_hashtab(&info, room, 0) == FALSE || ft_links(&info, &str) == FALSE
		|| ft_visu(&info, str, best, 1) == FALSE)
		return (ft_error(info, str, best, FAIL_HASH));
	best = ft_bfs(&info, room, best);
	if (best.steps == NULL || best.nb_ways == NONE)
		return (ft_error(info, str, best, FAIL_BFS));
	ft_visu(&info, str, best, 2);
	ft_result(str, info, &best, 0);
	free(str);
	ft_clean_steps(&best, 1);
	ft_clean_free(&info);
	return (TRUE);
}
