/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 13:51:31 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/24 11:52:07 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

int		coord(t_input *t, t_room **r, int j)
{
	t_room	*s;

	(*r)->x = ft_atoi(t->line + j) - t->xmin;
	j++;
	while (t->line[j] != ' ')
		j++;
	(*r)->y = ft_atoi(t->line + j) - t->ymin;
	if (!(s = (t_room*)malloc(sizeof(*s))))
		return (0);
	s->next = NULL;
	s->type = 0;
	(*r)->next = s;
	*r = s;
	return (1);
}

int		get_room(t_input *t, t_room *r, int i, int j)
{
	r->type = 0;
	while (i < t->room_nb)
	{
		get_next_line(0, &t->line);
		if (t->line[0] == '#' && t->line[1] == '#')
		{
			r->type = (t->line[2] == 's' ? 1 : 2);
			free(t->line);
			get_next_line(0, &t->line);
		}
		if (t->line[0] != '#')
		{
			while ( t->line[j] != ' ')
				j++;
			if (!(r->name = (char*)malloc(sizeof(char) * (j + 1))))
				return (0);
			ft_strncpy(r->name, t->line, j);
			r->name[j] = '\0';
			coord(t, &r, j);
		}
		else
			i--;
		free(t->line);
		i++;
		j = 0;
	}
	return (1);
}

int		get_info(t_input *t, t_room *r, t_disp *d)
{
	int		i;

	i = 2;
	if (!(r = (t_room*)malloc(sizeof(*r))))
        return (0);
	r->next = NULL;
	t->first = r;
	get_next_line(0, &t->line);
	t->room_nb = ft_atoi(t->line + 1);
	while (t->line[i] != ' ')
		i++;
	t->xmax = ft_atoi(t->line + i);
	i++;
	while (t->line[i] != ' ')
		i++;
	t->ymax = ft_atoi(t->line + i);
	i++;
	while (t->line[i] != ' ')
		i++;
	t->xmin = ft_atoi(t->line + i);
	i++;
	while (t->line[i] != ' ')
		i++;
	t->ymin = ft_atoi(t->line + i);
	i++;
	while (t->line[i] != ' ')
		i++;
	t->link_nb = ft_atoi(t->line + i);
	free(t->line);
	get_next_line(0, &t->line);
	t->ant_nb = ft_atoi(t->line);
	free(t->line);
	t->xmax -= t->xmin;
	t->ymax -= t->ymin;
	d->delay = 1000 / t->room_nb;
	d->delay = (d->delay < 20 ? 0 : d->delay);
	return (get_room(t, r, 0, 0));
}
