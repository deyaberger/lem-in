/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:28:25 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/29 13:12:21 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

t_info	init_info(void)
{
	t_info	info;

	info.line = NULL;
	info.ant_nb = 0;
	info.room_nb = 0;
	info.link_nb = 0;
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
	room->q = 0;
	room->nbl = 0;
	room->weight = 0;
	room->opti = 0;
	room->used = 0;
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

void		ft_clean_all(t_info *info, t_room *room)
{
	size_t 	i;
	size_t 	j;
	size_t 	k;

	i = 0;
	j = 0;
	k = 0;
	room = NULL;
	while (i < info->room_nb * 10)
	{
		if (info->tab && info->tab[i] != NULL)
		{
			room = info->tab[i];
			free(room->name);
			while (j <= info->room_nb && room->link && room->link[j])
			{
				free(room->link[j]);
				j++;
			}
			free(room->link);
			free(room);
			j = 0;
		}
		i++;
	}
	i = 0;
	while ((int)i <= info->xmax && info->coord[i])
	{
		free(info->coord[i]);
		i++;
	}
	if (info->coord)
		free(info->coord);
	if (info->tab)
		free(info->tab);
}

int		main(void)
{
	t_info	info;
	t_room	*room;
	int		i;

	i = -1;
	info = init_info();
	room = init_room();
	info.first = room;
	if (!ft_storage(&info, room, i))
		error_exit(1, "ft_storage has failed");
	ft_hashtab(&info, room);
	ft_links(&info);
	ft_start_end(&info);
	ft_bfs(&info, room);
	ft_clean_all(&info, room);
	return (FALSE);
}

/*
   __attribute__((destructor))
   void    end()
   {
   while(1);
   }*/
