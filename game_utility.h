#ifndef GAME_UTILITY_H_INCLUDED
#define GAME_UTILITY_H_INCLUDED

#include "Texture_object.h"
#define GAME_OVER 1
#define WIN -1
struct Game_util{
    TextureObject background;
    int order_backgr;
    TextureObject but_tutorial;
    TextureObject tutorial;
    TextureObject but_exit;
    TextureObject but_newgame;
    TextureObject but_continue;
    TextureObject but_restart;
    bool can_continue;
    bool is_close_util;

    Game_util(SDL_Renderer *renderer);
    void update_backgr_util(const string& file, SDL_Renderer* renderer);
    void move_down(SDL_Renderer* renderer);
    void update_event(SDL_Event event, bool &is_quit, int &level, bool &start);
    void show(SDL_Renderer *renderer);
};

#endif // GAME_UTILITY_H_INCLUDED
