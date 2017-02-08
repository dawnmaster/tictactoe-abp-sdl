#include <SDL.h>
#include <conio.h>
#include <SDL_ttf.h>
#include <iostream>
#include "GUI.h"

int main(int argc, char *argv[])
{
	GUI gui(420, 420, 32, SDL_SWSURFACE, 24);
	gui.StateMachine();
	//_getch();
	return 0;
}