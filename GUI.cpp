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

void GUI::StartScreen()	///0
{
	///fill background
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 120, 120, 120));
	SDL_Rect rectangle;
	rectangle.x = screen->w / 2 - 80;
	rectangle.y = screen->h / 2 - 40;
	TTF_Font *font = TTF_OpenFont("ariblk.ttf", 40);
	SDL_Color color = { 103,183,226 };
	this->text = TTF_RenderText_Blended(font, "loading...", color);
	SDL_BlitSurface(text, NULL, screen, &rectangle);
	///refresh screen
	SDL_Flip(screen);
	//SDL_Delay(1000);
	this->ScreenSelected = 1;
	return;
}

void GUI::MenuScreen()	///1
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
	
	//std::cout << "asset loaded";
	//SDL_Delay(1000);

	SDL_Button play;
	play.Button_SetPosition(screen->w / 2 - 180, 320);
	play.Button_SetTextColor(255, 255, 50);
	play.Button_SetText("PLAY", "ariblk.ttf", 26);

	SDL_Button quit;
	quit.Button_SetPosition(screen->w / 2 + 40, 320);
	quit.Button_SetTextColor(255, 255, 50);
	quit.Button_SetText("QUIT", "ariblk.ttf", 26);

	int choice = 0;
	while (!choice)
	{
		play.Button_Show(event);
		quit.Button_Show(event);
		changesMade = 0;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				exit(1);
				break;
			}
		}
		
		///play button events
		if (play.Button_onMoveOver())
		{
			play.Button_SetBackgroundColor(100, 200, 250);
		}
		else
		{
			play.Button_SetBackgroundColor(0, 200, 250);
		}

		if (play.Button_OnClick())
		{
			changesMade = 1;
			this->ScreenSelected = 2;
			choice = 1;
		}

		///quit button events
		if (quit.Button_onMoveOver())
		{
			quit.Button_SetBackgroundColor(100, 200, 250);
		}
		else
		{
			quit.Button_SetBackgroundColor(0, 200, 250);
		}

		if (quit.Button_OnClick())
		{
			exit(1);
		}

		SDL_Flip(screen);
	}
	return;
}

void GUI::GameOverScreen()	///5
{
	SDL_Rect rect;
	rect.x = 60;
	rect.y = 100;
	SDL_Surface *alpha = SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 32, 100, 0, 0, 0);
	SDL_SetAlpha(alpha, SDL_SRCALPHA, 100);
	SDL_BlitSurface(alpha, NULL, screen, NULL);
	SDL_FreeSurface(alpha);
	int choice = 0;
	this->font = TTF_OpenFont("ariblk.ttf", 40);
	this->color.r = 188;
	this->color.g = 235;
	this->color.b = 48;
	if (a == 2)
	{
		text = TTF_RenderText_Blended(font, "ITS A DRAW", this->color);
	}
	else if (a == 1)
	{
		rect.x = 50;
		text = TTF_RenderText_Blended(font, "COMPUTER WINS", this->color);
	}
	else if (a == -1)
	{
		text = TTF_RenderText_Blended(font, "HUMAN WINS", this->color);
	}
	std::cout << " a=" << a << " ";

	SDL_BlitSurface(text, NULL, screen, &rect);

	SDL_Button replay;
	replay.Button_SetPosition(100, 200);
	replay.Button_SetWH(200, 50);
	replay.Button_SetText("PLAY AGAIN", "ariblk.ttf", 15);

	SDL_Button quit;
	quit.Button_SetPosition(100, 270);
	quit.Button_SetWH(200, 50);
	quit.Button_SetText("QUIT", "ariblk.ttf", 15);

	while (!choice)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				choice = 1;
				exit(1);
				break;
			};
		}
		replay.Button_Show(event);
		quit.Button_Show(event);
		///replay button events
		if (replay.Button_onMoveOver())
		{
			replay.Button_SetBackgroundColor(227, 87, 168);
		}
		else
		{
			replay.Button_SetBackgroundColor(222, 61, 153);
		}
		if (replay.Button_OnClick())
		{
			ScreenSelected = 2;
			choice = 1;
		}
		///quit button events
		if (quit.Button_onMoveOver())
		{
			quit.Button_SetBackgroundColor(227, 87, 168);
		}
		else
		{
			quit.Button_SetBackgroundColor(222, 61, 153);
		}
		if (quit.Button_OnClick())
		{
			exit(1);
		}

		SDL_Flip(screen);
	}
}

void GUI::LevelSelectionScreen()	///2
{
	SDL_WM_SetCaption("TIC TAC TOE", NULL);
	SDL_SetAlpha(screen, SDL_SRCALPHA, 240);
	SDL_Surface *background = IMG_Load("Assets/Background1.jpg");
	SDL_BlitSurface(background, NULL, screen, NULL);

	SDL_Rect rectangle;
	rectangle.x = screen->w / 2 - 185;
	rectangle.y = screen->h / 2 - 190;
	TTF_Font *font = TTF_OpenFont("ariblk.ttf", 40);
	SDL_Color color = { 255,255,100 };
	this->text = TTF_RenderText_Blended(font, "Choose Difficulty", color);
	SDL_BlitSurface(text, NULL, screen, &rectangle);

	SDL_Button easy;
	easy.Button_SetPosition(80, 120);
	easy.Button_SetWH(260, 70);
	easy.Button_SetText("EASY", "ariblk.ttf", 26);

	SDL_Button medium;
	medium.Button_SetPosition(80, 220);
	medium.Button_SetWH(260, 70);
	medium.Button_SetText("MEDIUM", "ariblk.ttf", 26);

	SDL_Button hard;
	hard.Button_SetPosition(80, 320);
	hard.Button_SetWH(260, 70);
	hard.Button_SetText("HARD", "ariblk.ttf", 26);

	int choice = 0;

	while (!choice)
	{
		easy.Button_Show(event);
		medium.Button_Show(event);
		hard.Button_Show(event);

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				choice = 1;
				exit(1);
			};
		}

		///easy BUTTON events
		if (easy.Button_onMoveOver())
		{
			easy.Button_SetBackgroundColor(225, 150, 60);
		}
		else
		{
			easy.Button_SetBackgroundColor(200, 100, 5);
		}
		if (easy.Button_OnClick())
		{
			game.setMaxDepth(1);	///Difficulty
			choice = 1;
			this->ScreenSelected = 3;
			SDL_WM_SetCaption("TIC TAC TOE - EASY", NULL);
		}

		///medium BUTTON events
		if (medium.Button_onMoveOver())
		{
			medium.Button_SetBackgroundColor(225, 150, 60);
		}
		else
		{
			medium.Button_SetBackgroundColor(200, 100, 5);
		}

		if (medium.Button_OnClick())
		{
			game.setMaxDepth(3);	///Difficulty
			choice = 1;
			this->ScreenSelected = 3;
			SDL_WM_SetCaption("TIC TAC TOE - MEDIUM", NULL);
		}

		///hard BUTTON events
		if (hard.Button_onMoveOver())
		{
			hard.Button_SetBackgroundColor(225, 150, 60);
		}
		else
		{
			hard.Button_SetBackgroundColor(200, 100, 5);
		}

		if (hard.Button_OnClick())
		{
			game.setMaxDepth(7);	///Difficulty
			choice = 1;
			this->ScreenSelected = 3;
			SDL_WM_SetCaption("TIC TAC TOE - HARD", NULL);
		}
		SDL_Flip(screen);
	}
	SDL_FreeSurface(background);
}

void GUI::PlaySelection()	///3
{
	color.r = 28;
	color.g = 10;
	color.b = 79;
	SDL_Surface *background = IMG_Load("Assets/Background2.jpg");
	SDL_BlitSurface(background, NULL, screen, NULL);

	SDL_Rect rectangle;
	rectangle.x = screen->w / 2 - 120;
	rectangle.y = screen->h / 2 - 150;
	font = TTF_OpenFont("ariblk.ttf", 40);
	color = { 255,255,100 };
	this->text = TTF_RenderText_Blended(font, "Move first?", color);
	SDL_BlitSurface(text, NULL, screen, &rectangle);

	SDL_Button yes;
	yes.Button_SetPosition(150, 180);
	yes.Button_SetWH(120, 70);
	yes.Button_SetText("YES", "ariblk.ttf", 26);

	SDL_Button no;
	no.Button_SetPosition(150, 280);
	no.Button_SetWH(120, 70);
	no.Button_SetText("NO", "ariblk.ttf", 26);

	int choice = 0;

	while (!choice)
	{
		yes.Button_Show(event);
		no.Button_Show(event);

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				choice = 1;
				exit(1);
				break;
			};
		}
		//yes Button events
		if (yes.Button_onMoveOver())
		{
			yes.Button_SetBackgroundColor(100, 200, 250);
		}
		else
		{
			yes.Button_SetBackgroundColor(0, 200, 250);
		}
		if (yes.Button_OnClick())
		{
			Side = NOUGHTS;
			choice = 1;
		}
		//no Button events
		if (no.Button_onMoveOver())
		{
			no.Button_SetBackgroundColor(100, 200, 250);
		}
		else
		{
			no.Button_SetBackgroundColor(0, 200, 250);
		}
		if (no.Button_OnClick())
		{
			Side = CROSSES;
			choice = 1;
		}
		SDL_Flip(screen);
	}
	SDL_FreeSurface(background);
	this->ScreenSelected = 4;
}

void GUI::RunGame()	///4
{
	int GameOver = 0;
	int changesMade = 1;
	game.RunGame();
	if (Side == CROSSES)
	{
		getMove();
	}
	while (!GameOver)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:

				GameOver = 1;
				exit(1);
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					changesMade = 1;
					x = event.button.x;
					y = event.button.y;
					getMove();
					if (this->GameOver() != 0)
					{
						GameOver = 1;
					}
					if (!GameOver)
					{
						getMove();
					}
					if (this->GameOver() != 0)
					{
						GameOver = 1;
					}
					if (!GameOver)
					{
						getMove();
					}
					break;
				};
				break;
			};
		}
		if (changesMade)
		{
			putBoard();
			updateBoardGUI();
			changesMade = 0;
		}
		SDL_Flip(screen);
	}
	if (GameOver)
	{
		this->a = this->GameOver();
		this->ScreenSelected = 5;
		return;
	}
}

void GUI::getMove()
{
	if (Side == CROSSES)
	{
		game.GetComputerMove(Side, game.getBoard());
		flipSide();
	}
	else if (Side == NOUGHTS)
	{
		if (game.getBoard().board[y / 133][x / 133] == 0)
		{
			game.GetHumanMove(Side, game.getBoard(), y / 133, x / 133);
			flipSide();
		}
	}
}

int GUI::GameOver()
{
	if (game.EvalThreeAllBoard(Side, game.getBoard()) == 1)
	{
		std::cout << "computer wins";
		return 1;
	}
	if (game.EvalThreeAllBoard(Side, game.getBoard()) == -1)
	{
		std::cout << "human wins";
		return -1;
	}
	if (!isEmpty())
	{
		std::cout << "its a draw";
		return 2;
	}
	return 0;
}

int GUI::isEmpty()
{
	for (int row = 0; row < game.getBoard().size; row++)
	{
		for (int col = 0; col < game.getBoard().size; col++)
		{
			if (game.getBoard().board[row][col] == EMPTY)
			{
				return 1;
			}
		}
	}
	return 0;
}

void GUI::flipSide()
{
	if (Side == CROSSES)
		Side = NOUGHTS;
	else
		Side = CROSSES;
}

void GUI::putBoard()
{
	SDL_BlitSurface(board, NULL, screen, NULL);
}

void GUI::updateBoardGUI()
{
	for (int row = 0; row < game.getBoard().size; row++)
	{
		for (int col = 0; col < game.getBoard().size; col++)
		{
			if (game.getBoard().board[row][col] == CROSSES)
			{
				SDL_Rect rect;
				rect.y = row * 145;
				rect.x = col * 140;

				SDL_BlitSurface(cross, NULL, screen, &rect);
			}
			if (game.getBoard().board[row][col] == NOUGHTS)
			{
				SDL_Rect rect;
				rect.y = row * 145;
				rect.x = col * 140;

				SDL_BlitSurface(nought, NULL, screen, &rect);
			}
		}
	}
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