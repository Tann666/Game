#ifndef GAME_MAP_H_INCLUDED
#define GAME_MAP_H_INCLUDED

#include "Texture_object.h"

const int SIZE_TILE = 50;

struct Game_map
{

    int MapIndex[14][24];
    TextureObject tileset[8];
    Game_map();
    void load_Map(const string &file);
    void import_TileSet(const string &file, SDL_Renderer *renderer);
    void show_map(SDL_Renderer *renderer);
};


#endif // GAME_MAP_H_INCLUDED
