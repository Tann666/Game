#include "SDL_utility.h"
#include "Texture_object.h"

using namespace std;

int main(int argc, char* argv[])
{
    SDL_Window *gwindow = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event e;

    initSDL(gwindow,renderer);

    SDL_RenderClear(renderer);

    TextureObject *background = new TextureObject();
    background->load_texture("img/Tae3.jpg",renderer);
    background->Set_dstRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    background->RenderTexture(renderer);

    SDL_RenderPresent(renderer);
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
        }
    }
    background->Clean_Object();
    background = NULL;
    quitSDL(gwindow,renderer);
    return 0;
}
