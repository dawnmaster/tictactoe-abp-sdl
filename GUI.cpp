#include "GUI.h"
#include <iostream>

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

void GUI::StartScreen()	//0
{
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 120, 120, 120));
	SDL_Rect rectangle;
	rectangle.x = screen->w / 2 - 80;
	rectangle.y = screen->h / 2 - 40;
	TTF_Font *font = TTF_OpenFont("ariblk.ttf", 40);
	SDL_Color color = { 103,183,226 };
	this->text = TTF_RenderText_Blended(font, "loading...", color);
	SDL_BlitSurface(text, NULL, screen, &rectangle);
	SDL_Flip(screen);
	SDL_Delay(1000);
	this->ScreenSelected = 1;
	return;
}

void GUI::MenuScreen()	//1
{
	color.r = 255;
	color.g = 255;
	color.b = 100;
	SDL_Rect rectangle;
	rectangle.x = 60;
	rectangle.y = 50;
	int changesMade = 1;
	text = TTF_RenderText_Blended(font, "TIC TAC TOE", color);
	SDL_Surface *background = IMG_Load("menuBack.bmp");
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 200, 0, 255));
	SDL_BlitSurface(background, NULL, screen, NULL);
	SDL_BlitSurface(text, NULL, screen, &rectangle);
	
	std::cout << "asset loaded";
	SDL_Delay(1000);

	this->ScreenSelected = 6;

	int Exit = 0;
	return;
}

void GUI::LevelSelectionScreen()
{

}

void GUI::PlaySelection()
{

}

void GUI::RunGame()
{

}

void GUI::GameOverScreen()	//6
{
		
}

void GUI::StateMachine()
{
	int GameOver = 0;
	while (!GameOver)
	{
		switch (ScreenSelected)
		{
		case 0:
			StartScreen();
			break;
		case 1:
			MenuScreen();
			break;
		case 2:
			LevelSelectionScreen();
			break;
		case 3:
			PlaySelection();
			break;
		case 4:
			RunGame();
			break;
		case 5:
			GameOverScreen();
			break;
		case 6:
			GameOver = 1;
			break;
		}
	}
}

GUI::~GUI()
{
	SDL_FreeSurface(board);
	SDL_FreeSurface(icon);
	SDL_FreeSurface(cross);
	SDL_FreeSurface(nought);
	if (text != NULL)
	{
		SDL_FreeSurface(text);
	}
}