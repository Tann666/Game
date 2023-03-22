#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "Texture_object.h"
using namespace std;

const int right = 1;
const int left = 2;
const int up = 3;
const int down = 4;

#define CHAR_SIZE_W   50
#define CHAR_SIZE_H   50
struct status
{
    int r; // ứng với char_fram[0]
    int l;  // ứng với char_fram[1]
    int u;    // ứng với char_fram[2]
    int d;  // ứng với char_fram[3]
    status(){
        r = 0;
        l = 0;
        u = 0;
        d = 0;
    }
};
struct Character
{
    TextureObject char_frame[6];
    // mỗi một trạng thái chuyển động sẽ tương ứng với 1 char_frame[i]
    int mPos_x, mPos_y;
    int x_vel, y_vel;
    Character();
    void load_frame(SDL_Renderer *renderer);
    void control(SDL_Event e);
    void update_control();
    void render_frame(SDL_Renderer *renderer);

};
#endif // CHARACTER_H_INCLUDED
