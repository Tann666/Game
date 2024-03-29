#ifndef GAME_MAP_H_INCLUDED
#define GAME_MAP_H_INCLUDED

#include "Texture_object.h"
#include <vector>

#define OBJ_SIZE_W  50
#define OBJ_SIZE_H  50
const int SIZE_TILE = 50;

struct Game_map
{

    int MapIndex[14][24];
    TextureObject tileset[8];
    vector<SDL_Rect> enemy_pos;
    vector<int> ene_direction;
    vector<SDL_Rect> star_pos;
    Game_map();
    void load_Map(const string &file);
    void import_TileSet(const string &file, SDL_Renderer *renderer);
    void show_map(SDL_Renderer *renderer);
};


#endif // GAME_MAP_H_INCLUDED
