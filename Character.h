#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "SDL_utility.h"
#include "Texture_object.h"
#include "Game_Map.h"

using namespace std;

#define CHAR_SIZE_W   50
#define CHAR_SIZE_H   50
struct status
{
    bool right, left, up, down;
    status()
    {
        right = false;
        left = false;
        up = false;
        down = false;
    }
};
struct Character
{
    SDL_Window *gwindow;
    SDL_Renderer *renderer;
    TextureObject char_frame[7];
    // mỗi một trạng thái chuyển động sẽ tương ứng với 1 char_frame[i]
    int frame;
    int mPos_x, mPos_y;
    int x_vel, y_vel;
    status status_before;
    status c_status;
    Character();
    void load_frame(SDL_Renderer *renderer);
    void move_right();
    void move_left();
    void move_up();
    void move_down();
    void control(SDL_Event e);
    void update_control(Game_map *map_);
    bool valid_collision(const int &index);
    bool dead_collision_(const int &index);
    void check_collision_hor(Game_map *map_);
    void check_collision_ver(Game_map *map_);
    void render_frame(SDL_Renderer *renderer);
    void restart(const SDL_Rect &start_rect);
    bool end_level(const SDL_Rect &end_rect);
};
#endif // CHARACTER_H_INCLUDED
