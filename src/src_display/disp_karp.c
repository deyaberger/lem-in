#include "../../include/display.h"

void        disp_b(t_disp *d, t_input *t, t_room *s, int i)
{
	int		j;
	t_room	*nb_one;

	if (SDL_SetRenderDrawColor(d->rend, 255, 255, 255, 250) < 0)
		error("(disp_karp.c) SDL_SetRenderDrawColor : ", d);
	get_next_line(0, &t->line);
	while (t->line[0] != '#')
	{
		i = 0;
		s = t->first;
		while (t->line[i] != ':')
			i++;
		while (ft_strncmp(s->name, t->line, i))
			s = s->next;
		nb_one = s;
		s = t->first;
		if (SDL_SetRenderTarget(d->rend, d->txt2) < 0)
			error("(disp_karp.c) SDL_SetRenderTarget : ", d);
		d->rback.x = nb_one->x * t->coefx + 50;
		d->rback.y = nb_one->y * t->coefy + 24;
		d->rback.w = 27;
		d->rback.h = 64;
		if (SDL_RenderCopy(d->rend, d->pilsB, NULL, &d->rback) < 0)
			error("(disp_karp.c) SDL_RenderCopy : ", d);
		if (SDL_SetRenderTarget(d->rend, NULL) < 0)
			error("(disp_karp.c) SDL_SetRenderTarget : ", d);
		d->rback.x = 0;
		d->rback.y = 0;
		if (SDL_QueryTexture(d->txt2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
			error("(disp_karp.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->txt2, NULL, &d->rback) < 0)
			error("(disp_karp.c) SDL_RenderCopy : ", d);
		SDL_RenderPresent(d->rend);
		SDL_Delay(500);
		j = 0;
		while (t->line[i])
		{
			j++;
			i++;
			if (t->line[i] == '-')
			{
				j--;
				if (SDL_SetRenderTarget(d->rend, d->txt2) < 0)
					error("(disp_karp.c) SDL_SetRenderTarget : ", d);
				while (ft_strncmp(s->name, t->line + (i - j), j))
					s = s->next;
				if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 100, nb_one->y * t->coefy + 100, s->x * t->coefx + 100, s->y * t->coefy + 100) < 0)
					error("(disp_karp.c) SDL_RenderDrawLine : ", d);
				if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 101, nb_one->y * t->coefy + 100, s->x * t->coefx + 101, s->y * t->coefy + 100) < 0)
					error("(disp_karp.c) SDL_RenderDrawLine : ", d);
				if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 99, nb_one->y * t->coefy + 100, s->x * t->coefx + 99, s->y * t->coefy + 100) < 0)
					error("(disp_karp.c) SDL_RenderDrawLine : ", d);
				if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 100, nb_one->y * t->coefy + 101, s->x * t->coefx + 100, s->y * t->coefy + 101) < 0)
					error("(disp_karp.c) SDL_RenderDrawLine : ", d);
				if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 100, nb_one->y * t->coefy + 99, s->x * t->coefx + 100, s->y * t->coefy + 99) < 0)
					error("(disp_karp.c) SDL_RenderDrawLine : ", d);
				d->rback.x = s->x * t->coefx + 50;
				d->rback.y = s->y * t->coefy + 24;
				d->rback.w = 27;
				d->rback.h = 64;
				if (SDL_RenderCopy(d->rend, d->pilsR, NULL, &d->rback) < 0)
					error("(disp_karp.c) SDL_RenderCopy : ", d);
				if (SDL_SetRenderTarget(d->rend, NULL) < 0)
					error("(disp_karp.c) SDL_SetRenderTarget : ", d);
				d->rback.x = 0;
				d->rback.y = 0;
				if (SDL_QueryTexture(d->txt2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
					error("(disp_karp.c) SDL_QueryTexture : ", d);
				if (SDL_RenderCopy(d->rend, d->txt2, NULL, &d->rback) < 0)
					error("(disp_karp.c) SDL_RenderCopy : ", d);
				SDL_RenderPresent(d->rend);
				j = 0;
				s = t->first;
				SDL_Delay(500);
			}
		}
		free(t->line);
		get_next_line(0, &t->line);
	}
}

void        disp_k(t_disp *d, t_input *t, t_room *s, int i)
{
	t_room		*nb_one;
	int			j;

	get_next_line(0, &t->line);
	while (t->line[0] != '#')
	{
		if (SDL_SetRenderTarget(d->rend, d->txt2) < 0)
			error("(disp_karp.c) SDL_SetRenderTarget : ", d);
		i = 0;
		j = 0;
		s = t->first;
		while (t->line[i] != '-')
			i++;
		while (ft_strncmp(s->name, t->line, i))
			s = s->next;
		nb_one = s;
		s = t->first;
		j = i;
		while (t->line[i] != ':')
			i++;
		while (ft_strncmp(s->name, t->line + j + 1, i - j - 1))
			s = s->next;
		if (t->line[i + 1] == '1')
		{
			if (SDL_SetRenderDrawColor(d->rend, 25, 152, 227, 250) < 0)
				error("(disp_karp.c) SDL_SetRenderDrawColor : ", d);
		}
		else
		{
			if (SDL_SetRenderDrawColor(d->rend, 127, 14, 78, 250) < 0)
				error("(disp_karp.c) SDL_SetRenderDrawColor : ", d);
		}
		if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 100, nb_one->y * t->coefy + 100, s->x * t->coefx + 100, s->y * t->coefy + 100) < 0)
			error("(disp_karp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 101, nb_one->y * t->coefy + 100, s->x * t->coefx + 101, s->y * t->coefy + 100) < 0)
			error("(disp_karp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 99, nb_one->y * t->coefy + 100, s->x * t->coefx + 99, s->y * t->coefy + 100) < 0)
			error("(disp_karp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 100, nb_one->y * t->coefy + 101, s->x * t->coefx + 100, s->y * t->coefy + 101) < 0)
			error("(disp_karp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 100, nb_one->y * t->coefy + 99, s->x * t->coefx + 100, s->y * t->coefy + 99) < 0)
			error("(disp_karp.c) SDL_RenderDrawLine : ", d);
		if (SDL_SetRenderTarget(d->rend, NULL) < 0)
			error("(disp_karp.c) SDL_SetRenderTarget : ", d);
		d->rback.x = 0;
		d->rback.y = 0;
		if (SDL_QueryTexture(d->txt2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
			error("(disp_karp.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->txt2, NULL, &d->rback) < 0)
			error("(disp_karp.c) SDL_RenderCopy : ", d);
		SDL_RenderPresent(d->rend);
		SDL_Delay(500);
		free(t->line);
		get_next_line(0, &t->line);
	}
}

void        disp_w(t_disp *d, t_input *t, t_room *s, int i)
{
	t_room		*nb_one;
	int			j;

	if (SDL_SetRenderTarget(d->rend, d->txt2) < 0)
		error("(disp_karp.c) SDL_SetRenderTarget : ", d);
	d->rback.x = 0;
	d->rback.y = 0;
	if (SDL_QueryTexture(d->txt, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp_karp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
		error("(disp_karp.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp_karp.c) SDL_SetRenderTarget : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 255, 170, 0, 250) < 0)
		error("(disp_karp.c) SDL_SetRenderDrawColor : ", d);
	get_next_line(0, &t->line);
	while (t->line[0] != '#')
	{
		i = 0;
		while (t->line[i])
		{
			j = 0;
			if (t->line[i] == '-')
			{
				if (SDL_SetRenderTarget(d->rend, d->txt2) < 0)
					error("(disp_karp.c) SDL_SetRenderTarget : ", d);
				s = t->first;
				j = i;
				if (j == 0)
				{
					s = t->first;
					while (s->type != 1)
						s = s->next;
					nb_one = s;
				}
				i++;
				while (t->line[i] && t->line[i] != '-')
					i++;
				while (ft_strncmp(s->name, t->line + j + 1, i - j - 1))
					s = s->next;
				if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 100, nb_one->y * t->coefy + 100, s->x * t->coefx + 100, s->y * t->coefy + 100) < 0)
					error("(disp_karp.c) SDL_RenderDrawLine : ", d);
				if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 101, nb_one->y * t->coefy + 100, s->x * t->coefx + 101, s->y * t->coefy + 100) < 0)
					error("(disp_karp.c) SDL_RenderDrawLine : ", d);
				if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 99, nb_one->y * t->coefy + 100, s->x * t->coefx + 99, s->y * t->coefy + 100) < 0)
					error("(disp_karp.c) SDL_RenderDrawLine : ", d);
				if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 100, nb_one->y * t->coefy + 101, s->x * t->coefx + 100, s->y * t->coefy + 101) < 0)
					error("(disp_karp.c) SDL_RenderDrawLine : ", d);
				if (SDL_RenderDrawLine(d->rend, nb_one->x * t->coefx + 100, nb_one->y * t->coefy + 99, s->x * t->coefx + 100, s->y * t->coefy + 99) < 0)
					error("(disp_karp.c) SDL_RenderDrawLine : ", d);
				if (SDL_SetRenderTarget(d->rend, NULL) < 0)
					error("(disp_karp.c) SDL_SetRenderTarget : ", d);
				d->rback.x = 0;
				d->rback.y = 0;
				if (SDL_QueryTexture(d->txt2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
					error("(disp_karp.c) SDL_QueryTexture : ", d);
				if (SDL_RenderCopy(d->rend, d->txt2, NULL, &d->rback) < 0)
					error("(disp_karp.c) SDL_RenderCopy : ", d);
				nb_one = s;
				SDL_RenderPresent(d->rend);
				SDL_Delay(500);
			}
		}
		free(t->line);
		get_next_line(0, &t->line);
	}
}

void        disp_karp(t_disp *d, t_input *t)
{
	t_room		*s;

	if (SDL_SetRenderTarget(d->rend, d->txt2) < 0)
		error("(disp_karp.c) SDL_SetRenderTarget : ", d);
	d->rback.x = 0;
	d->rback.y = 0;
	if (SDL_QueryTexture(d->txt, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp_karp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
		error("(disp_karp.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp_karp.c) SDL_SetRenderTarget : ", d);
	while (t->line[0] != '#')
	{
		get_next_line(0, &t->line);
		if (t->line[0] != '#')
			free(t->line);
	}
	while (t->line[0] != '#' || t->line[1] != '0')
	{
		if (t->line[0] == '#' && t->line[1] == 'B')
		{
			free(t->line);
			disp_b(d, t, s, 0);
		}
		else if (t->line[0] == '#' && t->line[1] == 'K')
		{
			free(t->line);
			disp_k(d, t, s, 0);
		}
		else if ((t->line[0] == '#' && t->line[1] == 'W') || (t->line[0] == '#' && t->line[1] == 'F'))
		{
			free(t->line);
			disp_w(d, t, s, 0);
		}
		if (t->line[0] != '#')
		{
			free(t->line);
			get_next_line(0, &t->line);
		}
	}
}
