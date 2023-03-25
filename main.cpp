#include "SDL_utility.h"
#include "Texture_object.h"
#include "Game_Map.h"
#include "Character.h"
using namespace std;

int main(int argc, char* argv[])
{
    SDL_Window *gwindow = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event e;

    initSDL(gwindow,renderer);

    SDL_RenderClear(renderer);

    TextureObject *background = new TextureObject();
    background->load_texture("img/background.png",renderer);
    background->Set_dstRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);


    Game_map *map_ = new Game_map();
    map_->load_Map("img/map2.txt");
    map_->import_TileSet("img/set.png",renderer);

    Character *koala = new Character();
    koala->load_frame(renderer);


    bool is_quit = false;
    while (!is_quit)
    {
        while (SDL_PollEvent(&e)!=0)
        {
            if (e.type == SDL_QUIT)
            {
                is_quit= true;
                break;
            }
            koala->control(e);
        }
        SDL_RenderClear(renderer);
        background->RenderTexture(renderer);
        map_->show_map(renderer);
        koala->restart(map_->tileset[1].dstrect);
        koala->update_control();
        koala->render_frame(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);

    }
    background->Clean_Object();
    background = NULL;
    quitSDL(gwindow,renderer);
    return 0;
}
