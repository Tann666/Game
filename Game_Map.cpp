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
    for (int i=0; i<8; i++)
    {
        tileset[i].load_texture(file,renderer);
        tileset[i].srcrect.w /=8;
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
        }
    }
}
