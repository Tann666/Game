#include "game_utility.h"
int y_fall = -SCREEN_HEIGHT;
int max_level = 8;
Game_util::Game_util(SDL_Renderer *renderer){
    order_backgr = 0;
    is_close_util = false;
    can_continue = false;
    background.load_texture("img/Koala runaway.png",renderer);
    background.Set_dstRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    but_newgame.load_texture("img/newgame.png", renderer);
    but_newgame.Set_dstRect(50, 50, 300, 100);
    but_continue.load_texture("img/continue.png", renderer);
    but_continue.Set_dstRect(50, 175, 300, 100);
    but_restart.load_texture("img/restart.png", renderer);
    but_restart.Set_dstRect(50, 300, 300, 100);
    but_tutorial.load_texture("img/tutorial.png", renderer);
    but_tutorial.Set_dstRect(50, 425, 300, 100);//vị trí của nút
    tutorial.load_texture("img/noteContent.png", renderer);
    tutorial.Set_dstRect(0, 0, 0, 0);
    but_exit.load_texture("img/Exit.png", renderer);
    but_exit.Set_dstRect(50, 550, 300, 100);

}
void Game_util::update_backgr_util(const string& file, SDL_Renderer* renderer){
    background.load_texture(file,renderer);
}
void Game_util::move_down(SDL_Renderer* renderer){
    background.Set_dstRect(0, y_fall, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (y_fall >= 0) {
        y_fall = 0;
        is_close_util = false;
    }
    else {
        y_fall += 8;
    }
    background.RenderTexture(renderer);
}
void Game_util::update_event(SDL_Event event, bool &is_quit, int &level, bool &start){
    if (event.type == SDL_MOUSEBUTTONUP){
        if (event.button.button == SDL_BUTTON_LEFT){
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            if (mouseX >= but_tutorial.dstrect.x && mouseX <= but_tutorial.dstrect.x + but_tutorial.dstrect.w
                && mouseY >= but_tutorial.dstrect.y && mouseY <= but_tutorial.dstrect.y + but_tutorial.dstrect.h){
                    if (tutorial.dstrect.w == 0)//nếu đang tắt tutor
                    tutorial.Set_dstRect(SCREEN_WIDTH / 2 - 150, (SCREEN_HEIGHT - 450) / 2, 675, 450);
                    else // nếu đang bật
                    tutorial.Set_dstRect(0, 0, 0, 0);
                }
            else if (mouseX >= but_exit.dstrect.x && mouseX <= but_exit.dstrect.x + but_exit.dstrect.w
                && mouseY >= but_exit.dstrect.y && mouseY <= but_exit.dstrect.y + but_exit.dstrect.h){
                is_quit = true;
                }
            else if (mouseX >= but_newgame.dstrect.x && mouseX <= but_newgame.dstrect.x + but_newgame.dstrect.w
                && mouseY >= but_newgame.dstrect.y && mouseY <= but_newgame.dstrect.y + but_newgame.dstrect.h){
                tutorial.Set_dstRect(0, 0, 0, 0);
                start = false;
                level = 1;
                is_close_util = true;
                y_fall = -SCREEN_HEIGHT;
                order_backgr = 0;
                cout<<"newgame\n";
                }
            else if (mouseX >= but_continue.dstrect.x && mouseX <= but_continue.dstrect.x + but_continue.dstrect.w
                && mouseY >= but_continue.dstrect.y && mouseY <= but_continue.dstrect.y + but_continue.dstrect.h){
                if (can_continue){
                    is_close_util = true;
                    tutorial.Set_dstRect(0, 0, 0, 0);
                }
                }
            else if (mouseX >= but_restart.dstrect.x && mouseX <= but_restart.dstrect.x + but_restart.dstrect.w
                && mouseY >= but_restart.dstrect.y && mouseY <= but_restart.dstrect.y + but_restart.dstrect.h){
                if (level <= max_level){
                    tutorial.Set_dstRect(0, 0, 0, 0);
                    start = false;
                    is_close_util = true;
                    y_fall = -SCREEN_HEIGHT;
                    order_backgr = 0;
                    cout<<"restart level "<<level<<endl;
                }
            }
        }
    }
}
void Game_util::show(SDL_Renderer *renderer){
    background.Set_dstRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    background.RenderTexture(renderer);
    but_tutorial.RenderTexture(renderer);
    tutorial.RenderTexture(renderer);
    but_exit.RenderTexture(renderer);
    but_newgame.RenderTexture(renderer);
    but_continue.RenderTexture(renderer);
    but_restart.RenderTexture(renderer);
}
