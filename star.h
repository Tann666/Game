#ifndef STAR_H_INCLUDED
#define STAR_H_INCLUDED

#include "Texture_object.h"
#include "Game_Map.h"

struct Star{
    TextureObject star_frame;
    int frame;
    Star(SDL_Renderer *renderer);
    void render_frame(SDL_Renderer *renderer);
    void restart(const SDL_Rect &start_rect);
};

#endif // STAR_H_INCLUDED
