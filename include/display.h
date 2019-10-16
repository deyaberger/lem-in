/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:26:01 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/15 14:33:40 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "lem-in.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "SDL2/SDL2_gfxPrimitives.h"
# include "SDL2/SDL2_imageFilter.h"
# include "SDL2/SDL2_rotozoom.h"
# include "SDL2/SDL2_framerate.h"

typedef struct      s_disp
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		event;
	SDL_Surface		*img;
	SDL_Texture		*back;
	SDL_Texture		*title;
	SDL_Texture		*start;
	SDL_Texture		*leave;
	SDL_Texture		*made;
	SDL_Texture		*arrow;
	SDL_Texture		*startW;
	SDL_Texture		*leaveW;
	SDL_Rect		rback;
	SDL_Rect		menu;
}					t_disp;

void				menu(t_disp *d, int *running, int cursor);
void				img(t_disp *d, SDL_Texture *tex, char *filename, SDL_Rect rback);
void				error(char *src, t_disp *d);

#endif
