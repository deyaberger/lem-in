#include "../../include/display.h"

void			init2(t_disp *d)
{
	if (SDL_ShowCursor(SDL_DISABLE) < 0)
		error("(main.c) SDL_ShowCursor : ", d);
	if (SDL_SetWindowFullscreen(d->win, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
		error("(main.c) SDL_SetWindowFullscreen error : ", d);
	if (SDL_SetWindowBrightness(d->win, 1.1) < 0)
		error("(main.c) SDL_SetWindowBrightness error : ", d);
	SDL_GetWindowSize(d->win, &d->w, &d->h);
	if ((d->txt = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, d->w, d->h)) == NULL)
		error("(main.c) SDL_CreateTexture : ", d);
	if ((d->txt2 = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, d->w, d->h)) == NULL)
		error("(main.c) SDL_CreateTexture : ", d);
	d->rback.x = 0;
	d->rback.y = 0;
	d->rback.w = 0;
	d->rback.h = 0;
}

void			init(t_disp *d)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		error("(main.c) SDL_Init error : ", d);
	if (!(d->win = SDL_CreateWindow("LEM-IN D/N", 200, 200,
					0, 0, SDL_WINDOW_OPENGL)))
		error("(main.c) SDL_CreateWindow error : ", d);
	if (!(d->rend = SDL_CreateRenderer(d->win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		error("(main.c) SDL_CreateRenderer error : ", d);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		error("(main.c) Mix_OpenAudio : ", d);
	Mix_VolumeMusic(30);
	if ((d->spy = Mix_LoadMUS("img/spy.ogg")) == NULL)
		error("(main.c) Mix_LoadMUS : ", d);
	if ((d->deft = Mix_LoadMUS("img/deftones.ogg")) == NULL)
		error("(main.c) Mix_LoadMUS : ", d);
	if ((d->wake = Mix_LoadMUS("img/wake.ogg")) == NULL)
		error("(main.c) Mix_LoadMUS : ", d);
	if (Mix_PlayMusic(d->spy, -1) == -1)
		error("(main.c) Mix_PlayMusic : ", d);
	init2(d);
}

void			init_img_load(t_disp *d, SDL_Texture **tex, char *filename)
{
	if (!(d->img = IMG_Load(filename)))
		error("(main.c) IMG_Load : ", d);
	if (!(*tex = SDL_CreateTextureFromSurface(d->rend, d->img)))
		error("(main.c) SDL_CreateTextureFromSurface : ", d);
	SDL_FreeSurface(d->img);
}

void			init_img2(t_disp *d)
{
	init_img_load(d, &d->Morph, "img/matrix/Morph.xcf");
	init_img_load(d, &d->MorphB, "img/matrix/MorphB.png");
	init_img_load(d, &d->MorphC, "img/matrix/MorphC.png");
	init_img_load(d, &d->MorphT, "img/matrix/MorphT.xcf");
	init_img_load(d, &d->Neo, "img/matrix/Neo.xcf");
	init_img_load(d, &d->NeoB, "img/matrix/NeoB.png");
	init_img_load(d, &d->NeoC, "img/matrix/NeoC.png");
	init_img_load(d, &d->NeoT, "img/matrix/NeoT.xcf");
	init_img_load(d, &d->Trini, "img/matrix/Trini.xcf");
	init_img_load(d, &d->TriniB, "img/matrix/TriniB.png");
	init_img_load(d, &d->TriniC, "img/matrix/TriniC.png");
	init_img_load(d, &d->TriniT, "img/matrix/TriniT.xcf");
	init_img_load(d, &d->Smith, "img/matrix/SmithB.xcf");
}

void			init_img(t_disp *d)
{
	init_img_load(d, &d->back, "img/back.jpg");
	init_img_load(d, &d->back2, "img/back2.jpg");
	init_img_load(d, &d->title, "img/title.xcf");
	init_img_load(d, &d->start, "img/start.xcf");
	init_img_load(d, &d->leave, "img/leave.xcf");
	init_img_load(d, &d->made, "img/made.xcf");
	init_img_load(d, &d->arrow, "img/arrow.xcf");
	init_img_load(d, &d->startW, "img/startW.xcf");
	init_img_load(d, &d->leaveW, "img/leaveW.xcf");
	init_img_load(d, &d->black, "img/black.jpg");
	init_img_load(d, &d->fail, "img/fail.jpg");
	init_img_load(d, &d->toss, "img/toss.png");
	init_img_load(d, &d->tossS, "img/tossS.png");
	init_img_load(d, &d->tossE, "img/tossE.png");
	init_img_load(d, &d->sub, "img/subject.xcf");
	init_img_load(d, &d->pilsB, "img/pilsB.xcf");
	init_img_load(d, &d->pilsR, "img/pilsR.xcf");
	init_img2(d);
}
