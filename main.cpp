#include "SDL_utility.h"
#include "Texture_object.h"
#include "Game_Map.h"
#include "Character.h"
#include <fstream>
#include <vector>

using namespace std;

int load_save_level();
void save_level(const int &level);
void add_backgr(vector<TextureObject>&background, const string &file, SDL_Renderer *renderer);
int main(int argc, char* argv[])
{
    SDL_Window *gwindow = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event e;

    int level = load_save_level();
    int backgr = 0;
    bool start = false;

    initSDL(gwindow,renderer);

    SDL_RenderClear(renderer);

    vector<TextureObject>background;
    add_backgr(background, "img/background1.png",renderer);
    add_backgr(background, "img/background2.png",renderer);
    add_backgr(background, "img/background3.png",renderer);
    add_backgr(background, "img/background4.png",renderer);
    add_backgr(background, "img/background5.png",renderer);
    add_backgr(background, "img/background6.png",renderer);
    add_backgr(background, "img/background7.png",renderer);

    Game_map *map_ = new Game_map();
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
                is_quit = true;
                break;
            }
            else koala->control(e);
        }
        if (!start)
        {
            switch (level)
            {
            case 1:
                map_->load_Map("img/map1.txt");
                break;
            case 2:
                map_->load_Map("img/map2.txt");
                break;
            }
            start = true;
            map_->show_map(renderer);
            koala->restart(map_->tileset[1].dstrect);
        }
        SDL_RenderClear(renderer);
        background[backgr].RenderTexture(renderer);
        map_->show_map(renderer);
        koala->update_control(map_);
        if (koala->end_level(map_->tileset[5].dstrect))
        {
            level ++;
            if (level > 2) level = 1;
            start = false;
            backgr ++;
            if (backgr >= (int)background.size()) backgr = 0;
        }
        koala->render_frame(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);

    }
    save_level(level);
    for (size_t i=0; i<background.size(); i++)
    {
        background[i].Clean_Object();
        background[i].texture_ = NULL;
    }
    quitSDL(gwindow,renderer);
    return 0;
}

int load_save_level()
{
    int n = -1;
    ifstream lv_File ("img/save_level.txt");
    while (!lv_File.eof())
    {
        if (lv_File)
        {
            lv_File>>n;
        }
        else cout<<"can't open save_level.txt file"<<endl;
    }
    lv_File.close();
    return n;
}
void save_level(const int &level)
{
    ofstream lv_File ("img/save_level.txt");
    if (lv_File)
    {
        lv_File<<level;
    }
    else cout<<"can't open save_level.txt file"<<endl;
    lv_File.close();
}
void add_backgr(vector<TextureObject>&background, const string &file, SDL_Renderer *renderer)
{
    TextureObject temp;
    temp.load_texture(file,renderer);
    temp.Set_dstRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    background.push_back(temp);
}
