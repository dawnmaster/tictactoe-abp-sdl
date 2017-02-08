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
	SDL_Surface *screen = nullptr;
	SDL_Surface *board = nullptr;
	SDL_Surface *cross = nullptr;
	SDL_Surface *nought = nullptr;
	SDL_Surface *text = nullptr;
	SDL_Surface *icon = nullptr;
	SDL_Color color;
	SDL_Event event;
	TTF_Font *font = nullptr;
	int FPS;
	int a, x, y;
	int Side;
	int ScreenSelected;
	enum { EMPTY, NOUGHTS, CROSSES };
	Tictactoe game;

public:
	GUI(int width, int height, int bpp, int flag, int fps);
	void putBoard();
	void getMove();
	void flipSide();
	void updateBoardGUI();
	int GameOver();
	void StartScreen();	//0
	void MenuScreen();	//1
	void LevelSelectionScreen();	//2
	void PlaySelection(); //3
	void RunGame(); //4
	void GameOverScreen(); //5
	void StateMachine();
	~GUI(void);
};