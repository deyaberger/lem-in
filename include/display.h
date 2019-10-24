/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:26:01 by ncoursol          #+#    #+#             */
/*   Updated: 2019/10/24 11:53:47 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "SDL2/SDL2_gfxPrimitives.h"
# include "SDL2/SDL2_imageFilter.h"
# include "SDL2/SDL2_rotozoom.h"
# include "SDL2/SDL2_framerate.h"
# include "SDL2/SDL_mixer.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"

typedef struct      s_disp
{
	int				w;
	int				h;
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		event;
	SDL_Surface		*img;
	SDL_Texture		*back;
	SDL_Texture		*back2;
	SDL_Texture		*black;
	SDL_Texture		*fail;
	SDL_Texture		*title;
	SDL_Texture		*start;
	SDL_Texture		*leave;
	SDL_Texture		*made;
	SDL_Texture		*arrow;
	SDL_Texture		*startW;
	SDL_Texture		*leaveW;
	SDL_Texture		*txt;
	SDL_Texture		*Morph;
	SDL_Texture		*Neo;
	SDL_Texture		*Trini;
	Mix_Music		*spy;
	Mix_Music		*wake;
	Mix_Music		*deft;
	Mix_Chunk		*menu1;
	Mix_Chunk		*menu2;
	SDL_Rect		rback;
	SDL_Rect		menu;
	int				delay;
}					t_disp;

typedef struct		s_input
{
	char			*line;
	int				ant_nb;
	int				room_nb;
	int				link_nb;
	int				xmax;
	int				ymax;
	int				xmin;
	int				ymin;
	float			coefx;
	float			coefy;
	struct s_room	*first;
}					t_input;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				type; //start(1) | end(2) | rien(0)
	struct s_room	*next;
}					t_room;

void				menu(t_disp *d, int *running, int cursor, int i);
//void				img(t_disp *d, SDL_Texture *tex, char *filename, int j);
void				error(char *src, t_disp *d);
void				disp(t_disp *d, t_input *t, int *mode);
int					get_info(t_input *t, t_room *r, t_disp *d);

#endif
