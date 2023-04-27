#include "Character.h"

const int speed = 10;
Character::Character()
{
    mPos_x = 0;
    mPos_y = 0;
    x_vel = 0;
    y_vel = 0;
    frame = 0;
    is_dead = false;
    is_win = false;
}
void Character::load_frame(SDL_Renderer *renderer)
{
    char_frame[0].load_texture("img\\right.png",renderer);
    char_frame[1].load_texture("img\\left.png",renderer);
    char_frame[2].load_texture("img\\up.png",renderer);
    char_frame[3].load_texture("img\\down.png",renderer);
    char_frame[4].load_texture("img\\move_horizontal.png",renderer);
    char_frame[5].load_texture("img\\move_vertical.png",renderer);

    for (int i = 0; i < 6; i++)
    {
        char_frame[i].srcrect.w /= 6;
        char_frame[i].Set_dstRect(mPos_x, mPos_y, CHAR_SIZE_W, CHAR_SIZE_H);
    }
}
void Character::move_right()
{
    if (!c_status.right && !c_status.left && !c_status.up && !c_status.down)
    {
        x_vel = speed;
        y_vel = 0;
        c_status.right = true;
        status_before.right = true;
        status_before.left = false;
        status_before.down = false;
        status_before.up = false;
    }
}
void Character::move_left()
{
    if (!c_status.right && !c_status.left && !c_status.up && !c_status.down)
    {
        x_vel = -speed;
        y_vel = 0;
        c_status.left = true;
        status_before.right = false;
        status_before.left = true;
        status_before.down = false;
        status_before.up = false;
    }
}
void Character::move_up()
{
    if (!c_status.right && !c_status.left && !c_status.up && !c_status.down)
    {
        x_vel = 0;
        y_vel = -speed;
        c_status.up = true;
        status_before.right = false;
        status_before.left = false;
        status_before.down = false;
        status_before.up = true;
    }
}
void Character::move_down()
{
    if (!c_status.right && !c_status.left && !c_status.up && !c_status.down)
    {
        x_vel = 0;
        y_vel = speed;
        c_status.down =true;
        status_before.right = false;
        status_before.left = false;
        status_before.down = true;
        status_before.up = false;
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
            move_right();
        }
        break;
        case SDLK_a:
        {
            move_left();
        }
        break;
        case SDLK_w:
        {
            move_up();
        }
        break;
        case SDLK_s:
        {
            move_down();
        }
        break;
        }
    }
}
void Character::update_control(Game_map *map_)
{
    mPos_x += x_vel;
    if ((mPos_x <= 0) || (mPos_x + CHAR_SIZE_W >= 24 * SIZE_TILE))
    {
        if (mPos_x < 0) mPos_x = 0;
        if (mPos_x + CHAR_SIZE_W > 24 * SIZE_TILE) mPos_x = 24 * SIZE_TILE - CHAR_SIZE_W;
        c_status.right = false;
        c_status.left = false;
    }
    else check_collision_hor(map_);
    mPos_y += y_vel;
    if ((mPos_y <= 0) || (mPos_y + CHAR_SIZE_H >= 14 * SIZE_TILE))
    {
        if (mPos_y < 0) mPos_y = 0;
        if (mPos_y + CHAR_SIZE_H > 14 * SIZE_TILE) mPos_y = 14 * SIZE_TILE - CHAR_SIZE_H;
        c_status.up = false;
        c_status.down = false;
    }
    else check_collision_ver(map_);
}
bool Character::valid_collision(const int &index)
{
    if (index > 0 && index != 6 && index != 7) return true;
    return false;
}
bool Character::dead_collision_(const int &index)
{
    if (index == 5) return true;
    return false;
}
void Character::check_collision_hor(Game_map *map_)
{
    int left = mPos_x / SIZE_TILE;
    int right = (mPos_x + CHAR_SIZE_W) / SIZE_TILE;
    int top = mPos_y / SIZE_TILE;
    int bottom = (mPos_y + CHAR_SIZE_H) / SIZE_TILE;

    if (bottom * SIZE_TILE == mPos_y + CHAR_SIZE_H) bottom -= 1;

    if (x_vel > 0)
    {
        if (valid_collision(map_->MapIndex[top][right]) || valid_collision(map_->MapIndex[bottom][right]))
        {
                if (dead_collision_(map_->MapIndex[top][right]) || dead_collision_(map_->MapIndex[bottom][right]))
                {
                    is_dead = true;
                }

                mPos_x = right * SIZE_TILE - CHAR_SIZE_W;
                c_status.right = false;
        }
    }
    else if (x_vel < 0)
    {
        if (valid_collision(map_->MapIndex[top][left]) || valid_collision(map_->MapIndex[bottom][left]))
        {
                if (dead_collision_(map_->MapIndex[top][left]) || dead_collision_(map_->MapIndex[bottom][left]))
                {
                    is_dead = true;
                }
                mPos_x = (left + 1) * SIZE_TILE;
                c_status.left = false;
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

    if (y_vel > 0)
    {
        if (valid_collision(map_->MapIndex[bottom][left]) || valid_collision(map_->MapIndex[bottom][right]))
        {
                if (dead_collision_(map_->MapIndex[bottom][left]) || dead_collision_(map_->MapIndex[bottom][right]))
                {
                    is_dead = true;
                }
                mPos_y = bottom * SIZE_TILE - CHAR_SIZE_H;
                c_status.down = false;
        }
    }
    else if (y_vel < 0)
    {
        if (valid_collision(map_->MapIndex[top][left]) || valid_collision(map_->MapIndex[top][right]))
        {
                if (dead_collision_(map_->MapIndex[top][left]) || dead_collision_(map_->MapIndex[top][right]))
                {
                    is_dead = true;
                }
                mPos_y = (top + 1) * SIZE_TILE;
                c_status.up = false;
        }
    }
}
void Character::render_frame(SDL_Renderer *renderer)
{
    for (int i = 0; i < 6; i++)
    {
        char_frame[i].Set_dstRect(mPos_x,mPos_y);
        char_frame[i].srcrect.x = frame/5 * char_frame[i].srcrect.w;
    }
    if (!c_status.right && !c_status.left && !c_status.up && !c_status.down)
    {
        if (status_before.right) char_frame[0].RenderTexture(renderer);
        else if (status_before.left) char_frame[1].RenderTexture(renderer);
        else if (status_before.up) char_frame[2].RenderTexture(renderer);
        else char_frame[3].RenderTexture(renderer);
    }
    else if (c_status.right || c_status.left)
    {
        char_frame[4].RenderTexture(renderer);
    }
    else if (c_status.up || c_status.down)
    {
        char_frame[5].RenderTexture(renderer);
    }
    frame++;
    if (frame >= 30) frame = 0;
}
void Character::restart(const SDL_Rect &start_rect)
{
    is_win = false;
    is_dead = false;
    mPos_x = start_rect.x;
    mPos_y = start_rect.y;
    x_vel = 0;
    y_vel = 0;
    c_status.right = false;
    c_status.left = false;
    c_status.up = false;
    c_status.down = false;
    status_before.right = false;
    status_before.left = false;
    status_before.up = false;
    status_before.down = false;
}
bool Character::end_level(const SDL_Rect &end_rect)
{
    if (mPos_x == end_rect.x && mPos_y == end_rect.y){
        x_vel = 0;
        y_vel = 0;
        c_status.right = false;
        c_status.left = false;
        c_status.up = false;
        c_status.down = false;
        return true;
    }
    return false;
}
void Character::end_status(){
    if (is_dead || is_win){
        x_vel = 0;
        y_vel = 0;
        c_status.right = false;
        c_status.left = false;
        c_status.up = false;
        c_status.down = false;
    }
}
