#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstring>
#include <iostream>
#include "SDL_button.h"
#include "Tictactoe.h"

class GUI
{
	SDL_Surface *screen;
	SDL_Surface *board;
	SDL_Surface *cross;
	SDL_Surface *nought;
	SDL_Surface *text;
	SDL_Surface *icon;
	SDL_Color color;
	//SDL_Event event;
	TTF_Font *font;
	int FPS;
	int a, x, y;
	int Side;
	int ScreenSelected;
	char text_t[20];
	enum { EMPTY, NOUGHTS, CROSSES };

public:
	GUI(int width, int height, int bpp, int flag, int fps);
	void StartScreen();	//0
	void MenuScreen();	//1
	void LevelSelectionScreen();	//2
	void PlaySelection(); //3
	void RunGame(); //4
	void GameOverScreen(); //5
	void StateMachine();
	~GUI(void);

};