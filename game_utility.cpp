#include "game_utility.h"

Game_util::Game_util(SDL_Renderer *renderer, int &level){
    is_close_util = false;
    background.load_texture("img/Koala runaway.png",renderer);
    background.Set_dstRect(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT);
    but_tutorial.load_texture("img/Note.png", renderer);
    but_tutorial.Set_dstRect(0, 0, 100, 100);//vị trí của nút
    tutorial.load_texture("img/noteContent.png", renderer);
    tutorial.Set_dstRect(0, 0, 0, 0);
    but_return.load_texture("img/Return.png", renderer);
    but_return.Set_dstRect(100, 0, 100, 100);
    but_exit.load_texture("img/Exit.png", renderer);
    but_exit.Set_dstRect(200, 0, 100, 100);
}
void Game_util::update_event(SDL_Event event, SDL_Renderer *renderer){
    if (event.type == SDL_KEYDOWN){
        if (event.key.keysym.sym == SDLK_SPACE) is_close_util = true;
    }//sự kiện tạm thời để check
}
void Game_util::show(SDL_Renderer *renderer){
    background.RenderTexture(renderer);
    but_tutorial.RenderTexture(renderer);
    tutorial.RenderTexture(renderer);
    but_return.RenderTexture(renderer);
    but_exit.RenderTexture(renderer);
}
