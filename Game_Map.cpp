#include <fstream>
#include "Game_Map.h"

using namespace std;

Game_map::Game_map(){};
void Game_map::load_Map(const string &file){
    ifstream file_ (file);
    while (!file_.eof()){
        if (file_){
            for (int i=0;i<14;i++){
                for (int j=0;j<24;j++){
                    file_>>MapIndex[i][j];
                }
            }
        }
    }
}
void Game_map::import_TileSet(const string &file, SDL_Renderer *renderer){
    for (int i=0;i<6;i++){
        tileset[i]->load_texture(file,renderer);
        tileset[i]->srcrect.x = i*SIZE_TILE;
        tileset[i]->srcrect.w /=6;
    }
}
