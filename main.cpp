#include "SDL_utility.h"
#include "Texture_object.h"
#include "Game_Map.h"
#include "Character.h"
#include <fstream>
#include <vector>
#include "Enemy.h"
#include "game_utility.h"

using namespace std;

int load_save_level();
void save_level(const int &level);
void add_backgr(vector<TextureObject>&background, const string &file, SDL_Renderer *renderer);
void init_enemy(SDL_Renderer *renderer, vector<enemy> &bats, vector<SDL_Rect> rect, vector<int> &direction);
bool char_vs_enemy(const int &c_posX, const int &c_posY, const int &e_posX, const int &e_posY);

int main(int argc, char* argv[])
{
    SDL_Window *gwindow = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event e;
    int max_level = 2;
    int level = load_save_level();
    int backgr = 0;
    bool start = false;

    initSDL(gwindow,renderer);

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

    vector <enemy> bats;

    Game_util *GameUtil = new Game_util(renderer,level);
    bool is_quit = false;
    cout<<"Start Game!"<<endl;
    while (!is_quit)
    {
        while (SDL_PollEvent(&e)!=0)
        {
            if (e.type == SDL_QUIT)
            {
                is_quit = true;
                cout<<"Out Game!"<<endl;
                break;
            }
            else if (!GameUtil->is_close_util) GameUtil->update_event(e,renderer);
            else{
                if (!koala->is_dead) koala->control(e);
                if (e.type == SDL_KEYDOWN){
                    if (e.key.keysym.sym == SDLK_ESCAPE) GameUtil->is_close_util = false;
                }
            }
        }
        if (!GameUtil->is_close_util) GameUtil->show(renderer);
        else {
            if (!start)
            {
                switch (level)
                {
                case 1:
                    {
                        map_->load_Map("img/map1.txt");
                        cout<<"level 1"<<endl;
                    }
                    break;
                case 2:
                    {
                        map_->load_Map("img/map2.txt");
                        cout<<"level 2"<<endl;
                    }
                    break;
                }
                start = true;
                map_->show_map(renderer);
                koala->restart(map_->tileset[1].dstrect);
                init_enemy(renderer, bats, map_->enemy_pos, map_->ene_direction);
            }
            SDL_RenderClear(renderer);
            background[backgr].RenderTexture(renderer);
            map_->show_map(renderer);
            koala->update_control(map_);

            for (size_t i = 0; i < bats.size(); i++){
                bats[i].ene_move(map_);
                bool tmp_is_dead = char_vs_enemy(koala->mPos_x, koala->mPos_y, bats[i].mPos_x, bats[i].mPos_y);
                if (tmp_is_dead){
                bats[i].stand_still();
                koala->is_dead = tmp_is_dead;
                }
            }
            koala->dead_status();
            //is_quit = koala->is_dead;
            if (koala->end_level(map_->tileset[5].dstrect))
            {
                level ++;
                if (level > max_level) //level = 1;
                {
                    is_quit = true;
                    cout<<"End Game!"<<endl;
                    level = 1;
                }
                bats.clear();
                cout<<"clear enemy!"<<endl;
                map_->enemy_pos.clear();
                start = false;
                backgr ++;
                if (backgr >= (int)background.size()) backgr = 0;
            }
            koala->render_frame(renderer);
            for (size_t i = 0; i < bats.size(); i++){
                bats[i].render_frame(renderer);
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(10);

    }//
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
void init_enemy(SDL_Renderer *renderer, vector<enemy> &bats, vector<SDL_Rect> rect, vector<int> &direction)
{
    for (size_t i = 0; i < rect.size(); i++){
        enemy bat(renderer);
        bat.restart(rect[i],direction[i]);
        bats.push_back(bat);
    }
}
bool char_vs_enemy(const int &c_posX, const int &c_posY, const int &e_posX, const int &e_posY)
{
    if ((c_posX == e_posX)&&(c_posY == e_posY)){
        cout<<"Game Over!"<<endl;
        return true;
    }
    return false;
}
