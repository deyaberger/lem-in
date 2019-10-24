/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:43:50 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/24 11:55:47 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void		error(char *src, t_disp *d)
{
	ft_printf("%s%s\n", src, SDL_GetError());
	//	SDL_FreeSurface(SDL_Surface* surface);
	//	SDL_DestroyTexture(SDL_Texture* texture);
	Mix_FreeMusic(d->deft);
	Mix_CloseAudio();
	SDL_DestroyRenderer(d->rend);
	SDL_DestroyWindow(d->win);
	SDL_Quit();
	exit(1);
}

void		init(t_disp *d)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		error("(main.c) SDL_Init error : ", d);
	if (!(d->win = SDL_CreateWindow("LEM-IN D/N", 200, 200,
					0, 0, SDL_WINDOW_OPENGL)))
		error("(main.c) SDL_CreateWindow error : ", d);
	if (!(d->rend = SDL_CreateRenderer(d->win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		error("(main.c) SDL_CreateRenderer error : ", d);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_VolumeMusic(15);
	d->spy = Mix_LoadMUS("img/spy.ogg");
	d->deft = Mix_LoadMUS("img/deftones.ogg");
	d->wake = Mix_LoadMUS("img/wake.ogg");
	Mix_PlayMusic(d->spy, -1);
	SDL_ShowCursor(SDL_DISABLE);
	if (SDL_SetWindowFullscreen(d->win , SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
		error("(main.c) SDL_SetWindowFullscreen error : ", d);
	if (SDL_SetWindowBrightness(d->win, 1.1) < 0)
		error("(main.c) SDL_SetWindowBrightness error : ", d);
	SDL_GetWindowSize(d->win, &d->w, &d->h);
	d->txt = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, d->w, d->h);
	d->rback.x = 0;
	d->rback.y = 0;
	d->rback.w = 0;
	d->rback.h = 0;
}

void		init_img2(t_disp *d, SDL_Texture **tex, char *filename)
{
	if (!(d->img = IMG_Load(filename)))
		error("(main.c) IMG_Load : ", d);
	if (!(*tex = SDL_CreateTextureFromSurface(d->rend, d->img)))
		error("(main.c) SDL_CreateTextureFromSurface : ", d);
	SDL_FreeSurface(d->img);
}

void		init_img(t_disp *d)
{
	init_img2(d, &d->back, "img/back.jpg");
	init_img2(d, &d->back2, "img/back2.jpg");
	init_img2(d, &d->title, "img/title.xcf");
	init_img2(d, &d->start, "img/start.xcf");
	init_img2(d, &d->leave, "img/leave.xcf");
	init_img2(d, &d->made, "img/made.xcf");
	init_img2(d, &d->arrow, "img/arrow.xcf");
	init_img2(d, &d->startW, "img/startW.xcf");
	init_img2(d, &d->leaveW, "img/leaveW.xcf");
	init_img2(d, &d->black, "img/black.jpg");
	init_img2(d, &d->fail, "img/fail.jpg");
	init_img2(d, &d->Morph, "img/Morph.png");
	init_img2(d, &d->Neo, "img/Neo.png");
	init_img2(d, &d->Trini, "img/Trini.png");
}

void		leave(t_disp *d, float i)
{
		if (SDL_QueryTexture(d->fail, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
			error("(main.c) SDL_QueryTexture : ", d);
		SDL_RenderCopy(d->rend, d->fail, NULL, &d->rback);
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
		SDL_RenderCopy(d->rend, d->black, NULL, &d->rback);
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
		Mix_VolumeMusic(25);
		Mix_FreeMusic(d->spy);
		Mix_PlayMusic(d->deft, -1);
		if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
			error("(main.c) SDL_QueryTexture : ", d);
		SDL_RenderCopy(d->rend, d->back2, NULL, NULL);
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
	float		i = 1.1;

	*running = 2;
	init(d);
	init_img(d);
	if (SDL_QueryTexture(d->back, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(main.c) SDL_QueryTexture : ", d);
	SDL_RenderCopy(d->rend, d->back, NULL, &d->rback);
	d->menu.w = d->rback.w / 3;
	d->menu.h = d->rback.h / 2;
	d->menu.x = d->rback.w / 3;
	d->menu.y = (d->rback.h / 3);
	menu(d, running, 1, 0);
	SDL_RenderClear(d->rend);
	d->rback.x = 0;
	d->rback.y = 0;
	Mix_FadeOutMusic(1000);
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
	while(running)
	{
		while(SDL_PollEvent(&d.event))
		{
			if(d.event.type == SDL_QUIT || d.event.key.keysym.sym == SDLK_q)
				running = 0;
		}
		disp(&d, &t, &mode);
	}
	Mix_CloseAudio();
	SDL_DestroyTexture(d.back);
	SDL_DestroyRenderer(d.rend);
	SDL_DestroyWindow(d.win);
	SDL_Quit();
	return (1);
}
