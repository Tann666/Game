#include "Character.h"


Character::Character(){
    mPos_x = 0;
    mPos_y = 0;
    x_vel = 0;
    y_vel = 0;
    frame = 0;
}
void Character::load_frame(SDL_Renderer *renderer){
    char_frame[0].load_texture("img\\right.png",renderer);
    char_frame[1].load_texture("img\\left.png",renderer);
    char_frame[2].load_texture("img\\up.png",renderer);
    char_frame[3].load_texture("img\\down.png",renderer);
    char_frame[4].load_texture("img\\move_horizontal.png",renderer);
    char_frame[5].load_texture("img\\move_vertical.png",renderer);

    for (int i = 0; i < 6; i++){
        char_frame[i].srcrect.x = 0;
        char_frame[i].srcrect.y = 0;
        char_frame[i].srcrect.w /= 6;
        char_frame[i].Set_dstRect(mPos_x, mPos_y, CHAR_SIZE_W, CHAR_SIZE_H);
    }
}
void Character::control(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN)// && e.key.repeat == 0)
        {
        switch (e.key.keysym.sym)
            {
            case SDLK_d://update trạng thái cđ, update x_vel hoặc y_vel
                {
                x_vel += 10;
                }
                break;
            case SDLK_a:
                {
                x_vel -=10;
                }
                break;
            case SDLK_w:
                {
                y_vel -= 10;
                }
                break;
            case SDLK_s:
                {
                y_vel += 10;
                }
                break;
            }
    }
}
void Character::update_control()
{
    mPos_x += x_vel;
    mPos_y += y_vel;
    if ((mPos_x < 0) || (mPos_x + CHAR_SIZE_W > 24 * SIZE_TILE))
        {
        mPos_x -= x_vel;
        }
    if ((mPos_y < 0) || (mPos_y + CHAR_SIZE_H > 14 * SIZE_TILE))
    {
        mPos_y -= y_vel;
    }

}
bool Character::check_collision()
{
    return false;
}
void Character::render_frame(SDL_Renderer *renderer)
{
    for (int i = 0; i < 6; i++){
        char_frame[i].Set_dstRect(mPos_x,mPos_y);
        char_frame[i].srcrect.x = frame * char_frame[i].srcrect.w;
    }
    if (c_status.r == 0 && c_status.l == 0 && c_status.u == 0 && c_status.d == 0){
        char_frame[3].RenderTexture(renderer);
    }
    if (frame >= 5) frame = 0;
    frame++;

}
void Character::restart(const SDL_Rect &start_rect)
{
    mPos_x = start_rect.x;
    mPos_y = start_rect.y;
}
