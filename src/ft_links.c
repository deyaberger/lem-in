/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:16:59 by dberger           #+#    #+#             */
/*   Updated: 2019/09/25 19:37:54 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

char		*ft_h2(char *line)
{
	int	i;
	int	j;
	char	*save;

	i = 0;
	j = 0;
	while (*line == '-' && *line)
		line++;
	while (*line != '-' && *line)
		line++;
	while (*line == '-' && *line)
		line++;
	save = line;
	if (ft_strchr(line, '-'))
	{
		while (save[i] != '-' && save[i])
			i++;
		j = i;
		while (save[j] && save[j] == '-')
			j++;
		if (save[j] != '\0')
			return (NULL);
		save[i] = '\0';
	}
	return (save);
}

char		*ft_h1(char *line)
{
	int 	i;
	char	*save;

	i = 0;
	while (*line == '-' && *line)
		line++;
	save = line;
	while (*line != '-' && *line)
	{
		line++;
		i++;
	}
	save[i] = '\0';
	return (save);
}

int		ft_fill_links(int h1, int h2, t_struct *t)
{
	unsigned int i;

	i = 0;
	while (t->tab[h1]->link[i] != -1 && t->tab[h1]->link[i] != h2 && i < t->room_nb)
		i++;
	if (t->tab[h1]->link[i] == h2)
		return (0);
	t->tab[h1]->link[i] = h2;
	if (i < t->room_nb - 1)
		t->tab[h1]->link[i + 1] = -1;
	i = 0;
	while (t->tab[h2]->link[i] != -1  && i < t->room_nb)
		i++;
	t->tab[h2]->link[i] = h1;
	if (i < t->room_nb - 1)
		t->tab[h2]->link[i + 1] = -1;
	return (1);
}

int		ft_links(t_struct *t)
{
	int		h1;
	int		h2;
	char	*room1;
	char	*room2;

	h1 = 0;
	h2 = 0;
	room1 = t->line;
	room2 = t->line;
	room2 = ft_h2(room2);
	room1 = ft_h1(room1);
	h2 = ft_hashage(room2, t->room_nb * 10);
	h1 = ft_hashage(room1, t->room_nb * 10); 
	if (t->tab[h1] == NULL || t->tab[h2] == NULL)
		return (0);
	ft_fill_links(h1, h2, t);
	free(t->line);
	while (get_next_line(0, &t->line))
	{
		if (t->line[0] == '#' && t->line[1] == '#')
		{
			free(t->line);
			return (0);
		}
		if (t->line[0] != '#')
		{
			room1 = t->line;
			room2 = t->line;
			room2 = ft_h2(room2);
			room1 = ft_h1(room1);
			h2 = ft_hashage(room2, t->room_nb * 10);
			h1 = ft_hashage(room1, t->room_nb * 10); 
			if (t->tab[h1] == NULL || t->tab[h2] == NULL)
				return (0);
			ft_fill_links(h1, h2, t);
		}
//		free(t->line);
	}
	return (1);
}
