#include "../../include/display.h"

void			disp_k3(t_disp *d, t_input *t, t_room **s, t_room **nb_one)
{
	if (SDL_RenderDrawLine(d->rend, (*nb_one)->x * t->coefx + 100,
				(*nb_one)->y * t->coefy + 100, (*s)->x * t->coefx + 100,
				(*s)->y * t->coefy + 100) < 0)
		error("(disp_karp.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, (*nb_one)->x * t->coefx + 101,
				(*nb_one)->y * t->coefy + 100, (*s)->x * t->coefx + 101,
				(*s)->y * t->coefy + 100) < 0)
		error("(disp_karp.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, (*nb_one)->x * t->coefx + 99,
				(*nb_one)->y * t->coefy + 100, (*s)->x * t->coefx + 99,
				(*s)->y * t->coefy + 100) < 0)
		error("(disp_karp.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, (*nb_one)->x * t->coefx + 100,
				(*nb_one)->y * t->coefy + 101, (*s)->x * t->coefx + 100,
				(*s)->y * t->coefy + 101) < 0)
		error("(disp_karp.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, (*nb_one)->x * t->coefx + 100,
				(*nb_one)->y * t->coefy + 99, (*s)->x * t->coefx + 100,
				(*s)->y * t->coefy + 99) < 0)
		error("(disp_karp.c) SDL_RenderDrawLine : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp_karp.c) SDL_SetRenderTarget : ", d);
}

int				disp_k2(t_disp *d, t_input *t, t_room **s, t_room **nb_one)
{
	int		j;
	int		i;

	i = 0;
	while (t->line[i] != '-')
		i++;
	while (ft_strncmp((*s)->name, t->line, i))
		*s = (*s)->next;
	*nb_one = *s;
	*s = t->first;
	j = i;
	while (t->line[i] != ':')
		i++;
	while (ft_strncmp((*s)->name, t->line + j + 1, i - j - 1))
		*s = (*s)->next;
	if (t->line[i + 1] == '1')
	{
		if (SDL_SetRenderDrawColor(d->rend, 25, 152, 227, 250) < 0)
			error("(disp_karp.c) SDL_SetRenderDrawColor : ", d);
	}
	else if (SDL_SetRenderDrawColor(d->rend, 127, 14, 78, 250) < 0)
		error("(disp_karp.c) SDL_SetRenderDrawColor : ", d);
	return (i);
}

void			disp_k(t_disp *d, t_input *t, t_room *s, int i)
{
	t_room		*nb_one;

	get_next_line(0, &t->line);
	while (t->line[0] != '#')
	{
		if (SDL_SetRenderTarget(d->rend, d->txt2) < 0)
			error("(disp_karp.c) SDL_SetRenderTarget : ", d);
		s = t->first;
		i = disp_k2(d, t, &s, &nb_one);
		disp_k3(d, t, &s, &nb_one);
		d->rback.x = 0;
		d->rback.y = 0;
		if (SDL_QueryTexture(d->txt2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
			error("(disp_karp.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->txt2, NULL, &d->rback) < 0)
			error("(disp_karp.c) SDL_RenderCopy : ", d);
		SDL_RenderPresent(d->rend);
		SDL_Delay(d->delay);
		event(d, 0, 1);
		free(t->line);
		get_next_line(0, &t->line);
	}
}
