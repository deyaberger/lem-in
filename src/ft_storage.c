/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_storage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 15:13:04 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/24 16:19:38 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int		ft_store(t_struct *t, t_room **r, int type)
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
	if (!((*r)->name = (char*)malloc(sizeof(char) * i)))
		return (0);
	(*r)->name[i] = '\0';
	(*r)->name = ft_strncpy((*r)->name, t->line, i);
	(*r)->type = type;
	t->room_nb++;
	return (1);
}

int		ft_storage(t_struct *t, t_room *r)
{
	int		i;

	i = -1;
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
				return (-1);
		if (ft_strcmp(t->line, "##start") == 0)
			i = 1;
		else if (ft_strcmp(t->line, "##end") == 0)
			i = 2;
		else
			i = 0;
		free(t->line);
	}
	//////////////////////Display liste///////////////////////
	
	r = t->first;
	while (r != NULL)
	{
		ft_printf("name : [%s]\n", r->name);
		ft_printf("type : [%d]\n\n", r->type);
		r = r->next;
	}
	
	//////////////////////////////////////////////////////////
	return (1);
}
