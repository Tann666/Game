#ifndef GAME_UTILITY_H_INCLUDED
#define GAME_UTILITY_H_INCLUDED

#include "Texture_object.h"

struct Game_util{
    TextureObject background;
    TextureObject but_tutorial;
    TextureObject tutorial;
    TextureObject but_exit;
    TextureObject but_return;
    TextureObject but_newgame;
    TextureObject but_continue;
    bool is_close_util;

    Game_util(SDL_Renderer *renderer, int &level);
    void update_event(SDL_Event event, SDL_Renderer *renderer);
    void show(SDL_Renderer *renderer);
};

#endif // GAME_UTILITY_H_INCLUDED
