#include "GUI.h"

GUI::GUI(int width, int height, int bpp, int flag, int fps)
{
	TTF_Init();
	this->font = TTF_OpenFont("ariblk.ttf", 40);
	this->screen = SDL_SetVideoMode(width, height, 32, flag);
	color.r = 58;
	color.g = 177;
	color.b = 222;
	this->FPS = fps;
	this->board = SDL_LoadBMP("grid.bmp");
	this->cross = SDL_LoadBMP("cross.bmp");
	this->nought = SDL_LoadBMP("nought.bmp");
	this->icon = IMG_Load("icon1.ico");
	this->ScreenSelected = 0;
	SDL_WM_SetCaption("TicTacToe Main Screen", NULL);
	SDL_WM_SetIcon(icon, NULL);
}

