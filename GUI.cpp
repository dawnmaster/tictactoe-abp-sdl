#include "GUI.h"
#include <iostream>
#include <stdio.h>
#include <windows.h>

GUI::GUI(int width, int height, int bpp, int flag, int fps)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		exit(-1);
	}
	TTF_Init();
	this->font = TTF_OpenFont("ariblk.ttf", 40);
	this->screen = SDL_SetVideoMode(width, height, 32, flag);
	color.r = 58;
	color.g = 177;
	color.b = 222;
	this->FPS = fps;
	this->board = SDL_LoadBMP("Assets/grid.bmp");
	this->cross = SDL_LoadBMP("Assets/cross.bmp");
	this->nought = SDL_LoadBMP("Assets/nought.bmp");
	this->icon = IMG_Load("Assets/icon1.ico");
	this->ScreenSelected = 0;
	SDL_WM_SetCaption("TicTacToe Main Screen", NULL);
	SDL_WM_SetIcon(icon, NULL);
}

void GUI::putBoard()
{
}

void GUI::getMove()
{
}

void GUI::flipSide()
{
}

void GUI::updateBoardGUI()
{
}

int GUI::GameOver()
{
	return 0;
}

void GUI::StartScreen()	//0
{
	//fill background
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 120, 120, 120));
	SDL_Rect rectangle;
	rectangle.x = screen->w / 2 - 80;
	rectangle.y = screen->h / 2 - 40;
	TTF_Font *font = TTF_OpenFont("ariblk.ttf", 40);
	SDL_Color color = { 103,183,226 };
	this->text = TTF_RenderText_Blended(font, "loading...", color);
	SDL_BlitSurface(text, NULL, screen, &rectangle);
	//refresh screen
	SDL_Flip(screen);
	//SDL_Delay(1000);
	this->ScreenSelected = 1;
	return;
}

void GUI::MenuScreen()	//1
{
	color.r = 255;
	color.g = 255;
	color.b = 100;
	SDL_Rect rectangle;
	rectangle.x = 70;
	rectangle.y = 40;
	int changesMade = 1;
	text = TTF_RenderText_Blended(font, "TIC TAC TOE", color);	//this?
	SDL_Surface *background = IMG_Load("Assets/MenuBackground.bmp");
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 200, 0, 255));
	SDL_BlitSurface(background, NULL, screen, NULL);
	SDL_BlitSurface(text, NULL, screen, &rectangle);
	
	std::cout << "asset loaded";
	//SDL_Delay(1000);

	SDL_Button button1;
	button1.Button_SetPosition(screen->w / 2 - 180, 320);
	button1.Button_SetTextColor(255, 255, 50);
	button1.Button_SetText("PLAY", "ariblk.ttf", 26);

	SDL_Button button2;
	button2.Button_SetPosition(screen->w / 2 + 40, 320);
	button2.Button_SetTextColor(255, 255, 50);
	button2.Button_SetText("QUIT", "ariblk.ttf", 26);

	int Exit = 0;
	while (!Exit)
	{
		button1.Button_Show(event);
		button2.Button_Show(event);
		changesMade = 0;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				exit(1);
				break;
			default:
				break;
			}
		}
		
		//button 1 events
		if (button1.Button_onMoveOver())
		{
			button1.Button_SetBackgroundColor(100, 200, 250);
		}
		else
		{
			button1.Button_SetBackgroundColor(0, 200, 250);
		}

		if (button1.Button_OnClick())
		{
			changesMade = 1;
			this->ScreenSelected = 2;
			Exit = 1;
		}

		//button 2 events
		if (button2.Button_onMoveOver())
		{
			button2.Button_SetBackgroundColor(100, 200, 250);
		}
		else
		{
			button2.Button_SetBackgroundColor(0, 200, 250);
		}

		if (button2.Button_OnClick())
		{
			exit(1);
		}

		SDL_Flip(screen);
	}
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