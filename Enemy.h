#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Texture_object.h"
#include "Game_Map.h"

#define ENE_SIZE_W   50
#define ENE_SIZE_H   50

#define HOR_DIRECTION 1
#define VER_DIRECTION 2

struct enemy{
    TextureObject ene_frame;
    int frame;
    int mPos_x, mPos_y;
    int x_vel, y_vel;
    int direction;
    enemy(SDL_Renderer *renderer);
    void load_frame(SDL_Renderer *renderer);
    void ene_move(Game_map *map_);
    void stand_still();
    bool valid_collision(const int &index);
    bool check_collision_hor(Game_map *map_);
    bool check_collision_ver(Game_map *map_);
    void render_frame(SDL_Renderer *renderer);
    void restart(const SDL_Rect &start_rect, const int &direct);
};

#endif // ENEMY_H_INCLUDED
