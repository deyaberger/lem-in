/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:39:28 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/15 16:43:15 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void		menu2(t_disp *d, int cursor)
{
	if (SDL_SetRenderDrawBlendMode(d->rend,SDL_BLENDMODE_BLEND) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 120) < 0)
		error("(menu.c) SDL_SetRenderDrawColor error : ", d);
	if (SDL_RenderFillRect(d->rend, NULL) < 0)
		error("(menu.c) SDL_RenderFillRect error : ", d);
	if (SDL_SetRenderDrawBlendMode(d->rend,SDL_BLENDMODE_BLEND) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 138, 138, 138, 220) < 0)
		error("(menu.c) SDL_SetRenderDrawColor error : ", d);
	if (SDL_RenderFillRect(d->rend, &d->menu) < 0)
		error("(menu.c) SDL_RenderFillRect error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 250, 250, 250, 250) < 0)
		error("(menu.c) SDL_SetRenderDrawColor error : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->menu) < 0)
		error("(menu.c) SDL_RenderDrawRect error : ", d);
	d->rback.x = 879;
	d->rback.y = 0;
	img(d, d->title, "img/title.png", d->rback);
	d->rback.x = 750;
	d->rback.y = 600;
	if (cursor == 1)
		img(d, d->startW, "img/startW.png", d->rback);
	else
		img(d, d->start, "img/start.png", d->rback);
}

void		menu3(t_disp *d, int cursor)
{
	d->rback.x = 750;
	d->rback.y = 800;
	if (cursor == 1)
	{
		img(d, d->leave, "img/leave.png", d->rback);
		d->rback.x = 1200;
		d->rback.y = 550;
		img(d, d->arrow, "img/arrow.png", d->rback);
	}
	else
	{
		img(d, d->leaveW, "img/leaveW.png", d->rback);
		d->rback.x = 1200;
		d->rback.y = 750;
		img(d, d->arrow, "img/arrow.png", d->rback);
	}
	d->rback.x = 890;
	d->rback.y = 400;
	img(d, d->made, "img/made.png", d->rback);
	if (SDL_RenderDrawLine(d->rend, 1020, 700, 1550, 700) < 0)
		error("(menu.c) SDL_RenderDrawLine error : ", d);
	SDL_RenderPresent(d->rend);
}

void        menu(t_disp *d, int *running, int cursor)
{
	menu2(d, cursor);
	menu3(d, cursor);
	while (*running == 2)
	{
		while (SDL_PollEvent(&d->event))
		{
			if (d->event.type == SDL_QUIT)
				error("(menu.c) SDL_QUIT : ", d);
			if (d->event.key.keysym.sym == SDLK_DOWN
					|| d->event.key.keysym.sym == SDLK_UP)
			{
				d->rback.w = -1;
				d->rback.x = 0;
				d->rback.y = 0;
				img(d, d->back, "img/back.xcf", d->rback);
				if (d->event.key.keysym.sym == SDLK_DOWN)
					cursor = (cursor == 1 ? 0 : 0);
				if (d->event.key.keysym.sym == SDLK_UP)
					cursor = (cursor == 0 ? 1 : 1);
				menu(d, running, cursor);
				break ;
			}
			if (d->event.key.keysym.sym == SDLK_RETURN)
			{
				*running = (cursor == 0 ? 0 : 1);
				break ;
			}
		}
	}
}
