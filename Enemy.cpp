#include "Enemy.h"

const int ene_speed = 3;

enemy::enemy(SDL_Renderer *renderer)
{
    frame = 0;
    mPos_x = 0;
    mPos_y = 0;
    x_vel = ene_speed;
    y_vel = ene_speed;
    ene_frame.load_texture("img/enemy.png",renderer);
    ene_frame.srcrect.w /= 6;
    ene_frame.Set_dstRect(mPos_x, mPos_y, ENE_SIZE_W, ENE_SIZE_H);
}
bool enemy::valid_collision(const int &index)
{
    if (index > 0 && index != 2 && index != 6 && index != 7) return true;
    return false;
}
bool enemy::check_collision_hor(Game_map *map_)
{
    int left = mPos_x / SIZE_TILE;
    int right = (mPos_x + ENE_SIZE_W) / SIZE_TILE;
    int top = mPos_y / SIZE_TILE;
    int bottom = (mPos_y + ENE_SIZE_H) / SIZE_TILE;

    if (bottom * SIZE_TILE == mPos_y + ENE_SIZE_H) bottom -= 1;

    if (x_vel > 0)
    {
        if (valid_collision(map_->MapIndex[top][right]) || valid_collision(map_->MapIndex[bottom][right]))
        {
            mPos_x = right * SIZE_TILE - ENE_SIZE_W;
            return true;
        }
    }
    else if (x_vel < 0)
    {
        if (valid_collision(map_->MapIndex[top][left]) || valid_collision(map_->MapIndex[bottom][left]))
        {
            mPos_x = (left + 1) * SIZE_TILE;
            return true;
        }
    }
    return false;
}
bool enemy::check_collision_ver(Game_map *map_)
{
    int left = mPos_x / SIZE_TILE;
    int right = (mPos_x + ENE_SIZE_W) / SIZE_TILE;
    int top = mPos_y / SIZE_TILE;
    int bottom = (mPos_y + ENE_SIZE_H) / SIZE_TILE;

    if (right * SIZE_TILE == mPos_x + ENE_SIZE_W) right -= 1;

    if (y_vel > 0)
    {
        if (valid_collision(map_->MapIndex[bottom][left]) || valid_collision(map_->MapIndex[bottom][right]))
        {
            mPos_y = bottom * SIZE_TILE - ENE_SIZE_H;
            return true;
        }
    }
    else if (y_vel < 0)
    {
        if (valid_collision(map_->MapIndex[top][left]) || valid_collision(map_->MapIndex[top][right]))
        {
            mPos_y = (top + 1) * SIZE_TILE;
            return true;
        }
    }
    return false;
}
void enemy::ene_move(Game_map *map_)
{
    if (direction == VER_DIRECTION){
        if (check_collision_ver(map_)) y_vel *= -1;
        mPos_y += y_vel;

    }
    if (direction == HOR_DIRECTION){
        if (check_collision_hor(map_)) x_vel *= -1;
        mPos_x += x_vel;

    }
}
void enemy::stand_still(){
    x_vel = 0;
    y_vel = 0;
}
void enemy::render_frame(SDL_Renderer *renderer)
{
    for (int i = 0; i < 6; i++)
    {
        ene_frame.Set_dstRect(mPos_x,mPos_y);
        ene_frame.srcrect.x = frame / 5 * ene_frame.srcrect.w;
    }
    ene_frame.RenderTexture(renderer);
    frame++;
    if (frame >= 30) frame = 0;
}
void enemy::restart(const SDL_Rect &start_rect, const int &direct)
{
    mPos_x = start_rect.x;
    mPos_y = start_rect.y;
    direction = direct;
}

