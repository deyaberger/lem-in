/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:43:50 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/15 16:44:00 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void		error(char *src, t_disp *d)
{
	ft_printf("%s%s\n", src, SDL_GetError());
	//	SDL_FreeSurface(SDL_Surface* surface);
	//	SDL_DestroyTexture(SDL_Texture* texture);
	SDL_DestroyRenderer(d->rend);
	SDL_DestroyWindow(d->win);
	SDL_Quit();
	exit(1);
}

void		init(t_disp *d)
{
	if (!(d->win = SDL_CreateWindow("LEM-IN D/N", 200, 200,
		0, 0, SDL_WINDOW_OPENGL)))
		error("(main.c) SDL_CreateWindow error : ", d);
	if (!(d->rend = SDL_CreateRenderer(d->win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		error("(main.c) SDL_CreateRenderer error : ", d);
	d->img = 0;
	d->back = 0;
	d->title = 0;
	d->rback.x = 0;
	d->rback.y = 0;
	d->rback.w = 0;
	d->rback.h = 0;
	d->menu.x = 0;
	d->menu.y = 0;
	d->menu.w = 0;
	d->menu.h = 0;
}

void		img(t_disp *d, SDL_Texture *tex, char *filename, SDL_Rect rback)
{
	int		i;

	i = 0;
	while (filename[i])
		i++;
	if (ft_strcmp(filename + (i - 4), ".png"))
		if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			error("(main.c) IMG_Init : ", d);
	if (ft_strcmp(filename + (i - 4), ".jpg"))
		if(!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
			error("(main.c) IMG_Init : ", d);
	if (!(d->img = IMG_Load(filename)))
		error("(main.c) IMG_Load : ", d);
	if (!(tex = SDL_CreateTextureFromSurface(d->rend, d->img)))
		error("(main.c) SDL_CreateTextureFromSurface : ", d);
	SDL_FreeSurface(d->img);
	if (d->rback.w == -1)
		if (SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND) < 0)
			error("(main.c) SDL_SetTextureBlendMode : ", d);
	if (SDL_QueryTexture(tex, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(main.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, tex, NULL, &d->rback) < 0)
		error("(main.c) SDL_RenderCopy : ", d);
}

void		init_window(t_disp *d, int *running)
{
	*running = 2;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		error("(main.c) SDL_Init error : ", d);
	init(d);
	if (SDL_SetWindowFullscreen(d->win , SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
		error("(main.c) SDL_SetWindowFullscreen error : ", d);
	if (SDL_SetWindowBrightness(d->win, 1.1) < 0)
		error("(main.c) SDL_SetWindowBrightness error : ", d);
	d->rback.w = -1;
	img(d, d->back, "img/back.xcf", d->rback);
	d->menu.w = d->rback.w / 3;
	d->menu.h = d->rback.h / 2;
	d->menu.x = d->rback.w / 3;
	d->menu.y = (d->rback.h / 3);
	menu(d, running, 1);
	SDL_RenderClear(d->rend);
	d->rback.x = 0;
	d->rback.y = 0;
	img(d, d->back, "img/back.xcf", d->rback);
	SDL_RenderPresent(d->rend);
}

void		disp_room(t_disp *d, int *room, int *delay)
{
	//filledCircleRGBA(d->rend, *x, y, 50, 250, 0, 0, 250);
	SDL_RenderPresent(d->rend);
}

void		disp_karp(t_disp *d, int *room, int *delay)
{


	SDL_RenderPresent(d->rend);
}

void		disp_lem(t_disp *d, int *room, int *delay)
{


	SDL_RenderPresent(d->rend);
}

int			main(void)
{
	t_disp	d;
	int		running;
	int		room;
	int		karp;
	int		lem;
	int		delay;
	int		x;

	x = 100;
	room = 1;
	karp = 0;
	lem = 0;
	delay = 250;
	init_window(&d, &running);
	while(running)
	{
		while(SDL_PollEvent(&d.event))
		{
			if(d.event.type == SDL_QUIT || d.event.key.keysym.sym == SDLK_q)
				running = 0;
		}
		if (room == 1)
			disp_room(&d, &room, &delay);
		else if (karp == 1)
			disp_karp(&d, &karp, &delay);
		else if (lem == 1)
			disp_lem(&d, &lem, &delay);
		//SDL_Delay(delay);
		x += 4;
	}
	SDL_DestroyTexture(d.back);
	SDL_DestroyRenderer(d.rend);
	SDL_DestroyWindow(d.win);
	SDL_Quit();
}
