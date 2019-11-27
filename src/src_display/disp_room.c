#include "../../include/display.h"

void		disp_room3(t_disp *d, t_input *t, t_room **s)
{
	d->rback.x = ((*s)->x * t->coefx) + 75;
	d->rback.y = ((*s)->y * t->coefy) + 75;
	d->rback.w = 50;
	d->rback.h = 50;
	if (SDL_RenderCopy(d->rend, d->toss, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	*s = (*s)->next;
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

void		disp_room2(t_disp *d, t_input *t, t_room **s)
{
	if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->back2, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	d->rback.x = ((*s)->x * t->coefx) + 75;
	d->rback.y = ((*s)->y * t->coefy) + 75;
	d->rback.w = 50;
	d->rback.h = 50;
	if (SDL_RenderCopy(d->rend, d->toss, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	d->rback.x = 0;
	d->rback.y = 0;
	*s = (*s)->next;
	SDL_RenderPresent(d->rend);
	SDL_Delay(d->delay);
	event(d, 0, 1);
}

void		disp_room(t_disp *d, t_input *t)
{
	int		i;
	t_room	*s;

	i = 0;
	s = t->first;
	while (i++ < t->room_nb)
		disp_room2(d, t, &s);
	i = 0;
	s = t->first;
	if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
	if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->back2, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	while (i++ < t->room_nb)
	{
		disp_room3(d, t, &s);
		event(d, 0, 1);
	}
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
}
