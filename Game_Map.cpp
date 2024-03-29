#include <fstream>
#include "Game_Map.h"

using namespace std;

Game_map::Game_map() {};
void Game_map::load_Map(const string &file)
{
    ifstream file_ (file);
    while (!file_.eof())
    {
        if (file_)
        {
            for (int i=0; i<14; i++)
            {
                for (int j=0; j<24; j++)
                {
                    file_>>MapIndex[i][j];
                }
            }
        }
    }
    file_.close();
}
void Game_map::import_TileSet(const string &file, SDL_Renderer *renderer)
{
    for (int i=0; i<7; i++)
    {
        tileset[i].load_texture(file,renderer);
        tileset[i].srcrect.w /=7;
        tileset[i].srcrect.x = i*tileset[i].srcrect.w;
        tileset[i].srcrect.y = 0;

        tileset[i].Set_dstRect(0,0,SIZE_TILE,SIZE_TILE);

    }
}
void Game_map::show_map(SDL_Renderer *renderer)
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 24; j++)
        {
            int index = MapIndex[i][j];
            if (index > 0)
            {
                tileset[index-1].Set_dstRect(j*SIZE_TILE, i*SIZE_TILE);
                tileset[index-1].RenderTexture(renderer);
            }
            else if (index < 0)
            {
                if (index == -5){
                    SDL_Rect star_;
                    star_.x = j*SIZE_TILE;
                    star_.y = i*SIZE_TILE;
                    bool add_star = true;
                    for (size_t k = 0; k < star_pos.size(); k++){
                        if (star_.x == star_pos[k].x && star_.y == star_pos[k].y){
                            add_star = false;
                            break;
                        }
                    }
                    if (add_star)
                    {
                        star_pos.push_back(star_);
                    }
                }
                else{
                    SDL_Rect enemy_;
                    enemy_.x = j*SIZE_TILE;
                    enemy_.y = i*SIZE_TILE;
                    bool add_ene = true;
                    for (size_t k = 0; k < enemy_pos.size(); k++){
                        if (enemy_.x == enemy_pos[k].x && enemy_.y == enemy_pos[k].y){
                            add_ene = false;
                            break;
                        }
                    }
                    if (add_ene)
                    {
                        if (index == -1) ene_direction.push_back(1);
                        if (index == -2) ene_direction.push_back(2);
                        enemy_pos.push_back(enemy_);
                    }
                }
            }
        }
    }
}
