#include "star.h"

Star::Star(SDL_Renderer* renderer){
    frame = 0;
    star_frame.load_texture("img/stars.png",renderer);
    star_frame.srcrect.w /= 6;
    star_frame.Set_dstRect(0, 0, OBJ_SIZE_W, OBJ_SIZE_H);
}
void Star::render_frame(SDL_Renderer *renderer){
        for (int i = 0; i < 6; i++)
        {
            star_frame.srcrect.x = frame / 5 * star_frame.srcrect.w;
        }
        star_frame.RenderTexture(renderer);
        frame++;
        if (frame >= 30) frame = 0;
}
void Star::restart(const SDL_Rect &start_rect){
    star_frame.Set_dstRect(start_rect.x, start_rect.y);
}
