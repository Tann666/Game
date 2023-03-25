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
        char_frame[i].srcrect.w /= 6;
        char_frame[i].Set_dstRect(mPos_x, mPos_y, CHAR_SIZE_W, CHAR_SIZE_H);
    }
}
void Character::control(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
        switch (e.key.keysym.sym)
            {
            case SDLK_d://update trạng thái cđ, update x_vel hoặc y_vel
                {
                x_vel = 10;
                y_vel = 0;
                }
                break;
            case SDLK_a:
                {
                x_vel = -10;
                y_vel = 0;
                }
                break;
            case SDLK_w:
                {
                x_vel = 0;
                y_vel = -10;
                }
                break;
            case SDLK_s:
                {
                x_vel = 0;
                y_vel = 10;
                }
                break;
            }
    }
}
void Character::update_control(Game_map *map_)
{
    mPos_x += x_vel;
    if ((mPos_x < 0) || (mPos_x + CHAR_SIZE_W > 24 * SIZE_TILE))
    {
        mPos_x -= x_vel;
    }
    else check_collision_hor(map_);
    mPos_y += y_vel;
    if ((mPos_y < 0) || (mPos_y + CHAR_SIZE_H > 14 * SIZE_TILE))
    {
        mPos_y -= y_vel;
    }
    else check_collision_ver(map_);
}
bool Character::valid_collision(const int &index){
    if (index != 0 && index != 2 && index != 6 && index != 7) return true;
    return false;
}
void Character::check_collision_hor(Game_map *map_)
{
    int left = mPos_x / SIZE_TILE;
    int right = (mPos_x + CHAR_SIZE_W) / SIZE_TILE;
    int top = mPos_y / SIZE_TILE;
    int bottom = (mPos_y + CHAR_SIZE_H) / SIZE_TILE;

    if (bottom * SIZE_TILE == mPos_y + CHAR_SIZE_H) bottom -= 1;

    if (x_vel > 0){
        if (valid_collision(map_->MapIndex[top][right]) || valid_collision(map_->MapIndex[bottom][right]))
        {
            if (x_vel > 0) mPos_x = right * SIZE_TILE - CHAR_SIZE_W;
        }
    }
    else if (x_vel < 0){
        if (valid_collision(map_->MapIndex[top][left]) || valid_collision(map_->MapIndex[bottom][left]))
        {
            mPos_x = (left + 1) * SIZE_TILE;
        }
    }
}
void Character::check_collision_ver(Game_map *map_)
{
    int left = mPos_x / SIZE_TILE;
    int right = (mPos_x + CHAR_SIZE_W) / SIZE_TILE;
    int top = mPos_y / SIZE_TILE;
    int bottom = (mPos_y + CHAR_SIZE_H) / SIZE_TILE;

    if (right * SIZE_TILE == mPos_x + CHAR_SIZE_W) right -= 1;

    if (y_vel > 0){
        if (valid_collision(map_->MapIndex[bottom][left]) || valid_collision(map_->MapIndex[bottom][right]))
        {
            mPos_y = bottom * SIZE_TILE - CHAR_SIZE_H;
        }
    }
    else if (y_vel < 0){
        if (valid_collision(map_->MapIndex[top][left]) || valid_collision(map_->MapIndex[top][right]))
        {
            mPos_y = (top + 1) * SIZE_TILE;
        }
    }
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
