/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_storage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 15:13:04 by ncoursol          #+#    #+#             */
/*   Updated: 2019/12/03 16:27:02 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		ft_max_min(t_info *info, int mode, int i)
{
	long		a;

	a = ft_atol(info->line + i);
	if (a > 2147483647)
		return (FALSE);
	if (mode == 1)
	{
		if (info->xmax < a)
			info->xmax = a;
		if (info->xmin > a)
			info->xmin = a;
	}
	if (mode == 2)
	{
		if (info->ymax < a)
			info->ymax = a;
		if (info->ymin > a)
			info->ymin = a;
	}
	return (TRUE);
}

int     ft_check(t_info *info, int type, int i)
{
	int     j;

	j = 0;
	if (info->line[i - 1] != ' ' || info->line[i] < '0' || info->line[i] > '9')
		return (3);
	if (!ft_max_min(info, 1, i))
		return (3);
	if (info->line[0] == 'L')
		return (3);
	while (info->line[i] != ' ' && info->line[i])
	{
		if (info->line[i] < '0' || info->line[i] > '9')
			return (3);
		i++;
	}
	if (info->line[i] != ' ' || info->line[i + 1] < '0' || info->line[i + 1] > '9')
		return (3);
	i++;
	if (!ft_max_min(info, 2, i))
		return (3);
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

BOOL	ft_store(t_info *info, t_room **room, int type)
{
	t_room	*new;
	int	i;

	i = 0;
	if ((*room)->name != NULL)
	{
		new = init_room();
		(*room)->next = new;
		(*room) = new;
	}
	while (info->line[i] != ' ' && info->line[i])
	{
		if (info->line[i] == '-')
			return (FALSE);
		i++;
	}
	if (!((*room)->name = (char*)malloc(sizeof(char) * i + 1)))
		return (FALSE);
	(*room)->name[i] = '\0';
	(*room)->name = ft_strncpy((*room)->name, info->line, i);
	i = ft_check(info, type, i + 1);
	if (i == ROOM_START)
		info->start = (*room);
	if (i == ROOM_END)
		info->end = (*room);
	info->room_nb++;
	return (i == 3 ? FALSE : TRUE);
}

BOOL		ft_storage(t_info *info, t_room *room, char **str)
{
	int		type;
	int		ret;
	int		start;
	int		end;

	type = -1;
	start = 0;
	end = 0;
	ret = get_next_line(0, &info->line);
	if (ret == -1 || ret == 0 || info->line == NULL)
		return (FALSE);
	if (!(*str = ft_strjoin_nf(*str, info->line, 1, info)))
		return (FALSE);
	if (info->line == NULL)
		return (FALSE);
	while (info->line[++type])
		if (!ft_isdigit(info->line[type]))
			return (FALSE);
	type = -1;
	info->ant_nb = ft_atol(info->line);
	if (info->ant_nb <= 0 || info->ant_nb > 2147483647)
		return (FALSE);
	free(info->line);
	while (get_next_line(0, &info->line))
	{
		if (ft_strchr(info->line, ' ') == NULL && info->line[0] != '#')
			break ;
		if (info->line[0] != '#')
			if (!ft_store(info, &room, type))
				return (FALSE);
		if (ft_strcmp(info->line, "##start") == 0)
		{
			type = ROOM_START;
			if (start == 0)
				start = 1;
			else
				return (FALSE);
		}
		else if (ft_strcmp(info->line, "##end") == 0)
		{
			type = ROOM_END;
			if (end == 0)
				end = 1;
			else
				return (FALSE);
		}
		else
			type = ROOM_NORMAL;
		if (!(*str = ft_strjoin_nf(*str, info->line, 1, info)))
			return (FALSE);
		free(info->line);
	}
	if (start == 0 || end == 0)
		return (FALSE);
	if (info->xmax == 0 || info->ymax == 0)
		return (FALSE);
	return (ft_strcmp("", info->line) == 0 ? FALSE : TRUE);
}
