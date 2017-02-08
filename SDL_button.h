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

public:
	//initialize button
	SDL_Button(void);
	//displays button on the Screen
	void Button_Show(SDL_Event &events);
	//sets width and height of the button
	void Button_SetWH(int width, int height);
	//sets position of the button on the Screen
	void Button_SetPosition(int x, int y);
	//sets background color of the button
	void Button_SetBackgroundColor(int r, int g, int b);
	//sets text, font and size
	void Button_SetText(const char *text, const char *font_name, int size);
	//sets color of button text;
	void Button_SetTextColor(int r, int g, int b);
	//text won't be displayed
	void Button_NoText();
	//on mouse over
	int Button_onMoveOver();
	//on mouse down
	int Button_onMoveDown();
	//on mouse left click
	int Button_OnClick();
	~SDL_Button(void);

private:
	//button event handler
	void Button_Events();
};