#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "GUI.h"

class SDL_Button
{
	SDL_Rect rectangle;
	SDL_Surface *Screen = nullptr;
	SDL_Surface *text = nullptr;
	TTF_Font *font = nullptr;
	SDL_Color textColor;
	SDL_Event event;
	int color;
	int flag_notext;
	int flag_onMoveOver;
	int flag_onMoveDown;
	int flag_onClick;
	int x, y;
};