/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 12:12:20 by ncoursol          #+#    #+#             */
/*   Updated: 2019/11/22 16:02:46 by ncoursol         ###   ########.fr       */
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
	while (t->line[0] != 0)
	{
		i = 0;
		s = t->first;
		get_next_line(0, &t->line);
		if (t->line[0] == 0)
			break ;
		if (t->line[0] != '#')
		{
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
		}
		free(t->line);
		j++;
	}
	free(t->line);
	j = 0;
	if (SDL_SetRenderDrawColor(d->rend, 29, 128, 22, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	while (j != t->link_nb * 2)
	{
		if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x, pts[j].y, pts[j + 1].x, pts[j + 1].y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x + 1, pts[j].y, pts[j + 1].x + 1, pts[j + 1].y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x - 1, pts[j].y, pts[j + 1].x - 1, pts[j + 1].y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x, pts[j].y + 1, pts[j + 1].x, pts[j + 1].y + 1) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x, pts[j].y - 1, pts[j + 1].x, pts[j + 1].y - 1) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		j += 2;
		SDL_RenderPresent(d->rend);
		SDL_Delay(d->delay);
	}
	j = 0;
	while (j != t->link_nb * 2)
	{
		if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
			error("(disp.c) SDL_SetRenderTarget : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x, pts[j].y, pts[j + 1].x, pts[j + 1].y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x + 1, pts[j].y, pts[j + 1].x + 1, pts[j + 1].y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x - 1, pts[j].y, pts[j + 1].x - 1, pts[j + 1].y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x, pts[j].y + 1, pts[j + 1].x, pts[j + 1].y + 1) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x, pts[j].y - 1, pts[j + 1].x, pts[j + 1].y - 1) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		j += 2;
		if (SDL_SetRenderTarget(d->rend, NULL) < 0)
			error("(disp.c) SDL_SetRenderTarget : ", d);
		if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
		SDL_RenderPresent(d->rend);
		SDL_Delay(d->delay);
	}
	i = 0;
	s = t->first;
	if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
		error("(disp.c) SDL_SetRenderTarget : ", d);
	while (i < t->room_nb)
	{
		d->rback.x = (s->x * t->coefx) + 75;
		d->rback.y = (s->y * t->coefy) + 75;
		d->rback.w = 50;
		d->rback.h = 50;
		if (s->type == 1)
		{
			if (SDL_RenderCopy(d->rend, d->tossS, NULL, &d->rback) < 0)
				error("(disp.c) SDL_RenderCopy : ", d);
			t->xmax = s->x;
			t->ymax = s->y;
		}
		else if (s->type == 2)
		{
			if (SDL_RenderCopy(d->rend, d->tossE, NULL, &d->rback) < 0)
				error("(disp.c) SDL_RenderCopy : ", d);
		}
		else
		{
			if (SDL_RenderCopy(d->rend, d->toss, NULL, &d->rback) < 0)
				error("(disp.c) SDL_RenderCopy : ", d);
		}
		s = s->next;
		i++;
		if (SDL_SetRenderTarget(d->rend, NULL) < 0)
			error("(disp.c) SDL_SetRenderTarget", d);
		d->rback.x = 0;
		d->rback.y = 0;
		if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
			error("(disp.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
		SDL_RenderPresent(d->rend);
		SDL_Delay(d->delay);
		if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
			error("(disp.c) SDL_SetRenderTarget", d);
	}
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
}

void        disp_room(t_disp *d, t_input *t)
{
	int		i;
	t_room	*s;

	s = t->first;
	while (i < t->room_nb)
	{
		if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
			error("(disp.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->back2, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
		d->rback.x = (s->x * t->coefx) + 75;
		d->rback.y = (s->y * t->coefy) + 75;
		d->rback.w = 50;
		d->rback.h = 50;
		if (SDL_RenderCopy(d->rend, d->toss, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
		d->rback.x = 0;
		d->rback.y = 0;
		s = s->next;
		i++;
		SDL_RenderPresent(d->rend);
		SDL_Delay(d->delay);
	}
	i = 0;
	s = t->first;
	if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
	if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->back2, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	while (i < t->room_nb)
	{
		d->rback.x = (s->x * t->coefx) + 75;
		d->rback.y = (s->y * t->coefy) + 75;
		d->rback.w = 50;
		d->rback.h = 50;
		if (SDL_RenderCopy(d->rend, d->toss, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
		s = s->next;
		i++;
		if (SDL_SetRenderTarget(d->rend, NULL) < 0)
			error("(disp.c) SDL_SetRenderTarget", d);
		d->rback.x = 0;
		d->rback.y = 0;
		if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
			error("(disp.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
		SDL_RenderPresent(d->rend);
		SDL_Delay(d->delay);
		if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
			error("(disp.c) SDL_SetRenderTarget", d);
	}
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
}

void		disp_choice(t_disp *d, t_input *t, int *c, int i)
{
	d->rback.y = 0;
	d->rback.x = 0;
	if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	d->menu.w = (d->rback.w / 4) * 2;
	d->menu.h = (d->rback.h / 4) * 2;
	d->menu.x = (d->rback.w / 2) - (d->menu.w / 2);
	d->menu.y =	(d->rback.h / 2) - (d->menu.h / 2);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
		error("(disp.c) SDL_SetRenderDrawBlendMode : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderFillRect(d->rend, &d->menu) < 0)
		error("(disp.c) SDL_RenderFillRect : ", d);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_NONE) < 0)
		error("(disp.c) SDL_SetRenderDrawBlendMode : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 29, 128, 22, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->menu) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	d->rback.w = 200;
	d->rback.h = 200;
	d->rback.y = (d->menu.h + d->menu.y) - 220;
	d->rback.x = d->menu.x + 20;
	if (*c == 0)
	{
		if (SDL_RenderCopy(d->rend, d->NeoC, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	else
	{
		if (SDL_RenderCopy(d->rend, d->NeoB, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	d->rback.x = d->menu.x + 240;
	if (*c == 1)
	{
		if (SDL_RenderCopy(d->rend, d->TriniC, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	else
	{
		if (SDL_RenderCopy(d->rend, d->TriniB, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	d->rback.x = d->menu.x + 460;
	if (*c == 2)
	{
		if (SDL_RenderCopy(d->rend, d->MorphC, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	else
	{
		if (SDL_RenderCopy(d->rend, d->MorphB, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	d->menu.w -= 24;
	d->menu.h = 60;
	d->menu.x += 12;
	d->menu.y += 12;
	if (SDL_RenderCopy(d->rend, d->sub, NULL, &d->menu) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 29, 128, 22, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->menu) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	d->menu.h = 400;
	d->menu.y += 72;
	if (*c == 0)
	{
		if (SDL_RenderCopy(d->rend, d->NeoT, NULL, &d->menu) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	else if (*c == 1)
	{
		if (SDL_RenderCopy(d->rend, d->TriniT, NULL, &d->menu) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	else
	{
		if (SDL_RenderCopy(d->rend, d->MorphT, NULL, &d->menu) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	if (SDL_SetRenderDrawColor(d->rend, 29, 128, 22, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->menu) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	SDL_RenderPresent(d->rend);
	while (*c < 3)
	{
		while (SDL_PollEvent(&d->event))
		{
			if (d->event.type == SDL_QUIT)
				error("(disp.c) SDL_QUIT : ", d);
			if ((d->event.key.keysym.sym == SDLK_LEFT
						|| d->event.key.keysym.sym == SDLK_RIGHT)
					&& d->event.type == SDL_KEYDOWN && i == 0)
			{
				if ((*c == 0 && d->event.key.keysym.sym == SDLK_RIGHT) 
						|| (*c == 2 && d->event.key.keysym.sym == SDLK_LEFT) || *c == 1)
					Mix_PlayChannel(-1, d->menu1, 0);
				if (d->event.key.keysym.sym == SDLK_RIGHT)
					*c += (*c == 2 ? 0 : 1);
				if (d->event.key.keysym.sym == SDLK_LEFT)
					*c -= (*c == 0 ? 0 : 1);
				disp_choice(d, t, c, i);
				break ;
			}
			if (d->event.key.keysym.sym == SDLK_RETURN)
			{
				d->rback.y = 0;
				d->rback.x = 0;
				if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
					error("(disp.c) SDL_QueryTexture : ", d);
				if (Mix_PlayChannel(-1, d->menu2, 0) == -1)
					error("(disp.c) Mix_PlayChannel : ", d);
				if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
					error("(disp.c) SDL_RenderCopy : ", d);
				SDL_RenderPresent(d->rend);
				*c += 3;
				break ;
			}
			if (d->event.type == SDL_KEYUP)
				i = 0;
		}
	}
}

int			lem(t_disp *d, t_input *t, int c)
{
	int		**ant;
	int		i;
	int		j;
	int		k;
	t_room	*s;

	i = 0;
	if (!(ant = (int**)malloc(sizeof(int*) * t->ant_nb)))
		return (0);
	while (i < t->ant_nb)
	{
		if (!(ant[i] = (int*)malloc(sizeof(int) * 2)))
			return (0);
		ant[i][0] = (t->xmax * t->coefx) + 100;
		ant[i][1] = (t->ymax * t->coefy) + 100;
		i++;
	}
	while (t->line[0] != 'L')
	{
		get_next_line(0, &t->line);
		if (t->line[0] != 'L')
			free(t->line);
	}
	d->delay = 6;
	while (t->line[0] != '#')
	{
		t->link_nb = 0;
		while (t->link_nb == 0)
		{
			t->link_nb = 1;
			i = 0;
			d->rback.x = 0;
			d->rback.y = 0;
			if (SDL_QueryTexture(d->txt, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
				error("(disp.c) SDL_QueryTexture : ", d);
			if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
				error("(disp.c) SDL_RenderCopy : ", d);
			while (t->line[i])
			{
				if (t->line[i] == 'L')
				{
					s = t->first;
					k = ft_atoi(t->line + i + 1) - 1;
					t->xmax = ant[k][0];
					t->ymax = ant[k][1];
					while (t->line[i - 1] != '-')
						i++;
					j = i;
					while (t->line[i] && t->line[i] != ' ')
						i++;
					while (ft_strncmp(s->name, t->line + j, i - j))
						s = s->next;
					t->xmin = (s->x * t->coefx) + 100;
					t->ymin = (s->y * t->coefy) + 100;
					ft_trace_line(t, d, (k == 0 ? c : 0));
					ant[k][0] = t->xmax;
					ant[k][1] = t->ymax;
					if (t->xmax != t->xmin || t->ymax != t->ymin)
						t->link_nb = 0;
				}
				while (SDL_PollEvent(&d->event))
				{
					if (d->event.type == SDL_QUIT)
						error("(disp.c) SDL_QUIT : ", d);
					if (d->event.key.keysym.sym == SDLK_ESCAPE)
					{
						d->delay = -1;
						error("End :D ", d);
					}
					if (d->event.key.keysym.sym == SDLK_KP_PLUS)
						d->delay = (d->delay == 40 ? 40 : d->delay + 1);
					if (d->event.key.keysym.sym == SDLK_KP_MINUS)
						d->delay = (d->delay == 0 ? 0 : d->delay - 1);
					if (d->event.key.keysym.sym == SDLK_r)
					{
						c -= 3;
						disp_choice(d, t, &c, i);
					}
				}
				if (t->line[i])
					i++;
			}
			SDL_RenderPresent(d->rend);
		}
		free(t->line);
		get_next_line(0, &t->line);
	}
	free(t->line);
	d->rback.x = 0;
	d->rback.y = 0;
	if (SDL_QueryTexture(d->txt, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
	return (1);
}

void		disp(t_disp *d, t_input *t)
{	
	int		w;
	int		h;
	int		c;

	c = 0;
	SDL_GetWindowSize(d->win, &w, &h);
	t->coefx = (((float)w - 200) / (float)t->xmax);
	t->coefy = (((float)h - 200) / (float)t->ymax);
	disp_room(d, t);
	disp_links(d, t);
	disp_karp(d, t);
	SDL_Delay(1000);
	disp_choice(d, t, &c, 0);
	lem(d, t, c);
}
