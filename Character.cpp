#include "Character.h"


Character::Character(){
    mPos_x = 0;
    mPos_y = 0;
    x_vel = 0;
    y_vel = 0;
}
void Character::load_frame(SDL_Renderer *renderer){
    char_frame[0].load_texture("img\\right.png",renderer);
    char_frame[0].srcrect.w /= 6;
    char_frame[0].Set_dstRect(0, 0, CHAR_SIZE_W, CHAR_SIZE_H);

    char_frame[1].load_texture("img\\left.png",renderer);
    char_frame[1].srcrect.w /= 6;
    char_frame[1].Set_dstRect(0, 0, CHAR_SIZE_W, CHAR_SIZE_H);

    char_frame[2].load_texture("img\\up.png",renderer);
    char_frame[2].srcrect.w /= 6;
    char_frame[2].Set_dstRect(0, 0, CHAR_SIZE_W, CHAR_SIZE_H);

    char_frame[3].load_texture("img\\down.png",renderer);
    char_frame[3].srcrect.w /= 6;
    char_frame[3].Set_dstRect(0, 0, CHAR_SIZE_W, CHAR_SIZE_H);

    char_frame[4].load_texture("img\\move_horizontal.png",renderer);
    char_frame[4].srcrect.w /= 6;
    char_frame[4].Set_dstRect(0, 0, CHAR_SIZE_W, CHAR_SIZE_H);

    char_frame[5].load_texture("img\\move_vertical.png",renderer);
    char_frame[5].srcrect.w /= 6;
    char_frame[5].Set_dstRect(0, 0, CHAR_SIZE_W, CHAR_SIZE_H);
}
void Character::control(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN){
        switch (e.key.keysym.sym)
            {
            case SDLK_d://update trạng thái cđ, update x_vel hoặc y_vel
                {

                }
                break;
            case SDLK_a:
                {

                }
                break;
            case SDLK_w:
                {

                }
                break;
            case SDLK_s:
                {

                }
                break;
            }
    }
}
void Character::update_control()
{

}
void Character::render_frame(SDL_Renderer *renderer)
{
    char_frame[0].RenderTexture(renderer);
    char_frame[1].RenderTexture(renderer);
    char_frame[2].RenderTexture(renderer);
    char_frame[3].RenderTexture(renderer);
    char_frame[4].RenderTexture(renderer);
    char_frame[5].RenderTexture(renderer);
}
