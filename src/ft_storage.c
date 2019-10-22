/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_storage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 15:13:04 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/21 13:49:44 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

BOOL		ft_coord(t_info *info)
{
	int		i;

	i = 0;
	if (!(info->coord = (int**)malloc(sizeof(int*) * (info->xmax + 1))))
		return (FALSE);
	while (i <= info->xmax)
	{
		if (!(info->coord[i] = (int*)malloc(sizeof(int) * (info->ymax + 1))))
			return (FALSE);
		ft_bzero(info->coord[i], (info->ymax + 1) * sizeof(int));
		i++;
	}
//////////////////display coord/////////////////////////
/*
	i = 0;
	int		j = 0;
	while (i <= info->xmax)
	{
		j = 0;
		while (j <= info->ymax)
		{
			ft_printf("%d", info->coord[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
*/
/////////////////////////////////////////////////////////
	return (TRUE);
}

void	ft_max(t_info *info, int mode, int i)
{
	int		a;

	a = ft_atoi(info->line + i);
	if (mode == 1)
		if (info->xmax < a)
			info->xmax = a;
	if (mode == 2)
		if (info->ymax < a)
			info->ymax = a;
}

int     ft_check(t_info *info, int type, int i)
{
	int     j;

	j = 0;
	ft_max(info, 1, i);
	if (info->line[0] == 'L')
		return (3);
	while (info->line[i] != ' ' && info->line[i])
	{
		if (info->line[i] < '0' || info->line[i] > '9')
			return (3);
		i++;
	}
	i++;
	ft_max(info, 2, i);
	while (info->line[i] != ' ' && info->line[i])
	{
		if (info->line[i] < '0' || info->line[i] > '9')
			return (3);
		i++;
	}
	i = -1;
	while (info->line[++i])
		if (info->line[i] == ' ')
			j++;
	return (j != 2 ? 3 : type);
}

BOOL		ft_store(t_info *info, t_room **room, int type)
{
	t_room	*new;
	int	i;

	i = 0;
	if ((*room)->type != -1)
	{
		new = init_room();
		(*room)->next = new;
		(*room) = new;
	}
	while (info->line[i] != ' ' && info->line[i])
		i++;
	if (!((*room)->name = (char*)malloc(sizeof(char) * i + 1)))
		return (FALSE);
	(*room)->name[i] = '\0';
	(*room)->name = ft_strncpy((*room)->name, info->line, i);
	(*room)->type = ft_check(info, type, i + 1);
	info->room_nb++;
	return ((*room)->type == 3 ? 0 : 1);
}

BOOL		ft_storage(t_info *info, t_room *room, int i)
{
	get_next_line(0, &info->line);
	while (info->line[++i])
		if (!ft_isdigit(info->line[i]))
			return (FALSE);
	info->ant_nb = ft_atoi(info->line);
	if (info->ant_nb <= 0 || info->ant_nb >= 2147483647)
		return (FALSE);
	free(info->line);
	while (get_next_line(0, &info->line))
	{
		if (ft_strchr(info->line, ' ') == NULL && info->line[0] != '#')
			break ;
		if (info->line[0] != '#')
			if (!ft_store(info, &room, i))
				return (FALSE);
		if (ft_strcmp(info->line, "##start") == 0)
			i = 1;
		else if (ft_strcmp(info->line, "##end") == 0)
			i = 2;
		else
			i = 0;
		free(info->line);
	}
	//////////////////////Display liste///////////////////////
/*	room = info->first;
	while (room != NULL)
	{
		ft_printf("name : [%s]\n", room->name);
		ft_printf("type : [%d]\n\n", room->type);
		room = room->next;
	}
//		ft_printf("xmax : [%d]\n", info->xmax);
//		ft_printf("ymax : [%d]\n\n", info->ymax);

	//////////////////////////////////////////////////////////
*/	return (ft_strcmp("", info->line) == 0 || !ft_coord(info) ? 0 : 1);
}
