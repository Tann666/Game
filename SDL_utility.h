#ifndef SDL_UTILITY_H_INCLUDED
#define SDL_UTILITY_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "Koala Runaway";

void logSDLError(ostream& os, const string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);


#endif // SDL_UTILITY_H_INCLUDED
