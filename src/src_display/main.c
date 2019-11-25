/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:43:50 by ncoursol          #+#    #+#             */
/*   Updated: 2019/11/22 17:27:19 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void		error(char *src, t_disp *d)
{
	if (d->delay != -1)
		ft_printf("%s%s\n", src, SDL_GetError());
	Mix_FreeMusic(d->deft);
	Mix_CloseAudio();
	SDL_DestroyRenderer(d->rend);
	SDL_DestroyWindow(d->win);
	SDL_Quit();
	exit(1);
}

void		leave(t_disp *d, float i)
{
	if (SDL_QueryTexture(d->fail, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(main.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->fail, NULL, &d->rback) < 0)
		error("(main.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
	while (i > 0)
	{
		if (SDL_SetWindowBrightness(d->win, i) < 0)
			error("(main.c) SDL_SetWindowBrightness error : ", d);
		SDL_Delay(100);
		i -= 0.1;
	}
	Mix_FreeMusic(d->spy);
	if (SDL_QueryTexture(d->black, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(main.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->black, NULL, &d->rback) < 0)
		error("(main.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
}

void		start(t_disp *d, float i)
{
	while (i > 0.1)
	{
		if (SDL_SetWindowBrightness(d->win, i) < 0)
			error("(main.c) SDL_SetWindowBrightness error : ", d);
		SDL_Delay(75);
		i -= 0.1;
	}
	Mix_VolumeMusic(0);
	Mix_FreeMusic(d->spy);
	if (Mix_PlayMusic(d->deft, -1) == -1)
		error("(main.c) SDL_Mix_PlayMusic : ", d);
	if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(main.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->back2, NULL, NULL) < 0)
		error("(main.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
	while (i < 1.1)
	{
		if (SDL_SetWindowBrightness(d->win, i) < 0)
			error("(main.c) SDL_SetWindowBrightness error : ", d);
		SDL_Delay(75);
		i += 0.1;
	}
}

void		init_window(t_disp *d, int *running)
{
	float	i;

	i = 1.1;
	*running = 2;
	init(d);
	init_img(d);
	if (SDL_QueryTexture(d->back, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(main.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->back, NULL, &d->rback) < 0)
		error("(main.c) SDL_RenderCopy : ", d);
	d->menu.w = d->rback.w / 3;
	d->menu.h = d->rback.h / 2;
	d->menu.x = d->rback.w / 3;
	d->menu.y = d->rback.h / 3;
	menu(d, running, 1, 0);
	if (SDL_RenderClear(d->rend) < 0)
		error("(main.c) SDL_RenderClear : ", d);
	d->rback.x = 0;
	d->rback.y = 0;
	if (Mix_FadeOutMusic(1000) == 0)
		error("(main.c) Mix_FadeOutMusic : ", d);
	if (*running != 1)
		leave(d, i);
	else
		start(d, i);
}

int			main(void)
{
	t_disp		d;
	t_input		t;
	t_room		*r;
	int			running;
	int			mode;

	mode = 0;
	get_info(&t, r, &d);
	init_window(&d, &running);
	while (running)
	{
		while (SDL_PollEvent(&d.event))
		{
			if (d.event.type == SDL_QUIT || d.event.key.keysym.sym == SDLK_q)
				running = 0;
		}
		if (mode == 0)
			disp(&d, &t);
		mode = 1;
	}
	Mix_CloseAudio();
	SDL_DestroyRenderer(d.rend);
	SDL_DestroyWindow(d.win);
	SDL_Quit();
	return (1);
}
