/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_storage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 15:13:04 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/18 14:41:10 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int8_t		ft_coord(t_info *t)
{
	int		i;

	i = 0;
	if (!(t->coord = (int**)malloc(sizeof(int*) * (t->xmax + 1))))
		return (0);
	while (i <= t->xmax)
	{
		if (!(t->coord[i] = (int*)malloc(sizeof(int) * (t->ymax + 1))))
			return (0);
		ft_bzero(t->coord[i], (t->ymax + 1) * sizeof(int));
		i++;
	}
//////////////////display coord/////////////////////////
/*
	i = 0;
	int		j = 0;
	while (i <= t->xmax)
	{
		j = 0;
		while (j <= t->ymax)
		{
			ft_printf("%d", t->coord[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
*/
/////////////////////////////////////////////////////////
	return (1);
}

void	ft_max(t_info *t, int mode, int i)
{
	int		a;

	a = ft_atoi(t->line + i);
	if (mode == 1)
		if (t->xmax < a)
			t->xmax = a;
	if (mode == 2)
		if (t->ymax < a)
			t->ymax = a;
}

int     ft_check(t_info *t, int type, int i)
{
	int     j;

	j = 0;
	ft_max(t, 1, i);
	if (t->line[0] == 'L')
		return (3);
	while (t->line[i] != ' ' && t->line[i])
	{
		if (t->line[i] < '0' || t->line[i] > '9')
			return (3);
		i++;
	}
	i++;
	ft_max(t, 2, i);
	while (t->line[i] != ' ' && t->line[i])
	{
		if (t->line[i] < '0' || t->line[i] > '9')
			return (3);
		i++;
	}
	i = -1;
	while (t->line[++i])
		if (t->line[i] == ' ')
			j++;
	return (j != 2 ? 3 : type);
}

int8_t		ft_store(t_info *t, t_room **r, int type)
{
	t_room	*n = NULL;
	int		i;

	i = 0;
	if ((*r)->type != -1)
	{
		n = init_room(n);
		(*r)->next = n;
		*r = n;
	}
	while (t->line[i] != ' ' && t->line[i])
		i++;
	if (!((*r)->name = (char*)malloc(sizeof(char) * i + 1)))
		return (0);
	(*r)->name[i] = '\0';
	(*r)->name = ft_strncpy((*r)->name, t->line, i);
	(*r)->type = ft_check(t, type, i + 1);
	t->room_nb++;
	return ((*r)->type == 3 ? 0 : 1);
}

int8_t		ft_storage(t_info *t, t_room *r, int i)
{
	get_next_line(0, &t->line);
	while (t->line[++i])
		if (!ft_isdigit(t->line[i]))
			return (0);
	t->ant_nb = ft_atoi(t->line);
	if (t->ant_nb <= 0 || t->ant_nb >= 2147483647)
		return (0);
	free(t->line);
	while (get_next_line(0, &t->line))
	{
		if (ft_strchr(t->line, ' ') == NULL && t->line[0] != '#')
			break ;
		if (t->line[0] != '#')
			if (!ft_store(t, &r, i))
				return (0);
		if (ft_strcmp(t->line, "##start") == 0)
			i = 1;
		else if (ft_strcmp(t->line, "##end") == 0)
			i = 2;
		else
			i = 0;
		free(t->line);
	}
	//////////////////////Display liste///////////////////////
/*
	r = t->first;
	while (r != NULL)
	{
		ft_printf("name : [%s]\n", r->name);
		ft_printf("type : [%d]\n\n", r->type);
		r = r->next;
	}
		ft_printf("xmax : [%d]\n", t->xmax);
		ft_printf("ymax : [%d]\n\n", t->ymax);
*/
	//////////////////////////////////////////////////////////
	return (ft_strcmp("", t->line) == 0 || !ft_coord(t) ? 0 : 1);
}
