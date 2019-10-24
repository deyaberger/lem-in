/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 12:12:20 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/24 14:11:06 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void        disp_links(t_disp *d, t_input *t)
{
	t_room		*s;
	SDL_Point	pts[t->link_nb * 2];
	int			i;
	int			j;

	j = 0;
	while (t->line[0] != '#')
	{
		i = 0;
		s = t->first;
		get_next_line(0, &t->line);
		if (t->line[0] == '#')
			break ;
		while (t->line[i] != '-')
			i++;
		while (ft_strncmp(s->name, t->line, i))
			s = s->next;
		pts[j].x = (s->x * t->coefx) + 100;
		pts[j].y = (s->y * t->coefy) + 100;
		j++;
		s = t->first;
		while (ft_strncmp(s->name, t->line + i + 1, ft_strlen(t->line) - i + 1))
			s = s->next;
		pts[j].x = (s->x * t->coefx) + 100;
		pts[j].y = (s->y * t->coefy) + 100;
		free(t->line);
		j++;
	}
	j = 0;
	while (j != t->link_nb * 2)
	{
		SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback);
		SDL_RenderDrawLine(d->rend, pts[j].x, pts[j].y, pts[j + 1].x, pts[j + 1].y);
		j += 2;
    	SDL_RenderPresent(d->rend);
		SDL_Delay(d->delay);
	}
	j = 0;
	while (j != t->link_nb * 2)
	{
		SDL_SetRenderTarget(d->rend, d->txt);
		SDL_RenderDrawLine(d->rend, pts[j].x, pts[j].y, pts[j + 1].x, pts[j + 1].y);
		j += 2;
		SDL_SetRenderTarget(d->rend, NULL);
		SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback);
    	SDL_RenderPresent(d->rend);
		SDL_Delay(d->delay);
	}
}

void        disp_room(t_disp *d, t_input *t)
{
	int		i;
	t_room	*s;

	s = t->first;
	while (i < t->room_nb)
	{
		if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
         error("(main.c) SDL_QueryTexture : ", d);
		SDL_RenderCopy(d->rend, d->back2, NULL, &d->rback);
    	filledCircleRGBA(d->rend, (s->x * t->coefx) + 100, (s->y * t->coefy) + 100, 10, 0, 250, 0, 250);
		s = s->next;
		i++;
    	SDL_RenderPresent(d->rend);
		SDL_Delay(d->delay);
	}
	i = 0;
	s = t->first;
	SDL_SetRenderTarget(d->rend, d->txt);
	if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
        error("(main.c) SDL_QueryTexture : ", d);
	SDL_RenderCopy(d->rend, d->back2, NULL, &d->rback);
	while (i < t->room_nb)
	{
    	filledCircleRGBA(d->rend, (s->x * t->coefx) + 100, (s->y * t->coefy) + 100, 10, 0, 250, 0, 250);
		s = s->next;
		i++;
		SDL_SetRenderTarget(d->rend, NULL);
		SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback);
    	SDL_RenderPresent(d->rend);
		SDL_Delay(d->delay);
		SDL_SetRenderTarget(d->rend, d->txt);
	}
	SDL_SetRenderTarget(d->rend, NULL);
}

void		disp(t_disp *d, t_input *t, int *mode)
{
	int		w;
	int		h;

	SDL_GetWindowSize(d->win, &w, &h);
	t->coefx = (((float)w - 200) / (float)t->xmax);
	t->coefy = (((float)h - 200) / (float)t->ymax);
	if (*mode == 0)
	{
		disp_room(d, t);
		disp_links(d, t);
	}
	*mode = 1;
}
