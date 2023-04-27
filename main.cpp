#include "koala.h"
using namespace std;

int load_save_level();
void save_level(const int &level, const int &max_level);
void add_backgr(vector<TextureObject>&background, const string &file, SDL_Renderer *renderer);
void init_enemy(SDL_Renderer *renderer, vector<enemy> &bats, vector<SDL_Rect> rect, vector<int> &direction);
bool char_vs_object(const SDL_Rect &ene_rect, const SDL_Rect &char_rect);
void init_stars(SDL_Renderer *renderer, vector<Star> &stars, vector<SDL_Rect> rect);
int main(int argc, char* argv[])
{
    SDL_Window *gwindow = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event e;
    int max_level = 8;
    int level = load_save_level();
    int backgr = 0;
    bool start = false;

    initSDL(gwindow,renderer);

    Mix_Music* beat = loadMusic("music/beat.mp3");
    playMusic(beat);
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
    vector <Star> stars;

    Game_util *GameUtil = new Game_util(renderer);
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
            else if (!GameUtil->is_close_util) GameUtil->update_event(e, is_quit, level, start);
            else{
                if (!koala->is_dead && !koala->is_win) koala->control(e);
                if (e.type == SDL_KEYDOWN){
                    if (e.key.keysym.sym == SDLK_ESCAPE) GameUtil->is_close_util = false;
                }
            }
        }
        if (!GameUtil->is_close_util) GameUtil->show(renderer);
        else {
            if (!start)
            {
                map_->ene_direction.clear();
                map_->enemy_pos.clear();
                map_->star_pos.clear();
                string filename = "img/map" + to_string(level) + ".txt";
                map_->load_Map(filename);
                cout<<"level "<<level<<endl;
                GameUtil->update_backgr_util("img/Koala runaway.png", renderer);
                GameUtil->can_continue = true;
                start = true;
                map_->show_map(renderer);
                koala->restart(map_->tileset[5].dstrect);
                cout<<"clear enemy!"<<endl;
                bats.clear();
                cout<<"clear stars!"<<endl;
                stars.clear();
                init_enemy(renderer, bats, map_->enemy_pos, map_->ene_direction);
                init_stars(renderer, stars, map_->star_pos);
            }
            SDL_RenderClear(renderer);
            background[backgr].RenderTexture(renderer);
            map_->show_map(renderer);
            koala->update_control(map_);

            for (size_t i = 0; i < bats.size(); i++){
                bats[i].ene_move(map_);
                SDL_Rect bat_rect = {bats[i].mPos_x, bats[i].mPos_y, OBJ_SIZE_W, OBJ_SIZE_H};
                SDL_Rect koala_rect = {koala->mPos_x, koala->mPos_y, CHAR_SIZE_W, CHAR_SIZE_H};
                bool tmp_is_dead = char_vs_object(bat_rect, koala_rect);
                if (tmp_is_dead){
                bats[i].stand_still();
                koala->is_dead = true;
                }
            }
            for (size_t i = 0; i < stars.size(); i++){
                SDL_Rect koala_rect = {koala->mPos_x, koala->mPos_y, CHAR_SIZE_W, CHAR_SIZE_H};
                bool pickup_star = char_vs_object(stars[i].star_frame.dstrect, koala_rect);
                if (pickup_star){
                    stars.erase(stars.begin()+i);
                    cout<<"pick up star!\n";
                }
            }
            koala->end_status();
            koala->render_frame(renderer);
            for (size_t i = 0; i < bats.size(); i++){
                bats[i].render_frame(renderer);
            }
            for (size_t i = 0; i < stars.size(); i++){
                stars[i].render_frame(renderer);
            }
            if (koala->is_dead){
                if (GameUtil->order_backgr != GAME_OVER){
                    GameUtil->update_backgr_util("img/gameover.png", renderer);
                    GameUtil->order_backgr = GAME_OVER;
                }
                GameUtil->move_down(renderer);
                GameUtil->can_continue = false;
            }
            if (koala->end_level(map_->tileset[6].dstrect))
            {
                if (stars.size() != 0){
                    koala->is_dead = true;
                }
                else{
                    level++;
                    if (level > max_level)
                    {
                        if (GameUtil->order_backgr != WIN){
                            GameUtil->update_backgr_util("img/youwin.png", renderer);
                            GameUtil->order_backgr = WIN;
                        }
                        koala->is_win = true;
                        GameUtil->move_down(renderer);
                        GameUtil->can_continue = false;
                    }
                    else {
                        start = false;
                        backgr ++;
                        if (backgr >= (int)background.size()) backgr = 0;
                    }
                }
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(10);

    }//
    save_level(level, max_level);
    background.clear();
    bats.clear();
    stars.clear();
    delete map_;
    delete koala;
    delete GameUtil;
    Mix_FreeMusic(beat);
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
void save_level(const int &level, const int &max_level)
{
    ofstream lv_File ("img/save_level.txt");
    if (lv_File)
    {
        if (level <= max_level)
        lv_File<<level;
        else lv_File<<1;
        cout<<"save level"<<endl;
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
    cout << "init " << bats.size() << " enemies\n";
}
bool char_vs_object(const SDL_Rect &obj_rect, const SDL_Rect &char_rect)
{
    int border_w = OBJ_SIZE_W / 6;
    int border_h = OBJ_SIZE_H / 4;
    if (char_rect.x == obj_rect.x || char_rect.y == obj_rect.y){
        if (char_rect.x == obj_rect.x){
            if (char_rect.y >= obj_rect.y + border_h && char_rect.y <= obj_rect.y + OBJ_SIZE_H - border_h){
                return true;
            }
            if (char_rect.y + CHAR_SIZE_H >= obj_rect.y + border_h && char_rect.y + CHAR_SIZE_H <= obj_rect.y + OBJ_SIZE_H - border_h){
                return true;
            }
        }
        if (char_rect.y == obj_rect.y){
            if (char_rect.x >= obj_rect.x + border_w && char_rect.x <= obj_rect.x + OBJ_SIZE_W - border_w){
                return true;
            }
            if (char_rect.x + CHAR_SIZE_W >= obj_rect.x + border_w && char_rect.x + CHAR_SIZE_W <= obj_rect.x + OBJ_SIZE_W - border_w){
                return true;
            }
        }
    }
    else{
        if (char_rect.x >= obj_rect.x + border_w && char_rect.x <= obj_rect.x + OBJ_SIZE_W - border_w){
            if (char_rect.y >= obj_rect.y + border_h && char_rect.y <= obj_rect.y + OBJ_SIZE_H - border_h){
                return true;
            }
            if (char_rect.y + CHAR_SIZE_H >= obj_rect.y + border_h && char_rect.y + CHAR_SIZE_H <= obj_rect.y + OBJ_SIZE_H - border_h){
                return true;
            }
        }
        if (char_rect.x + CHAR_SIZE_W >= obj_rect.x + border_w && char_rect.x + CHAR_SIZE_W <= obj_rect.x + OBJ_SIZE_W - border_w){
            if (char_rect.y >= obj_rect.y + border_h && char_rect.y <= obj_rect.y + OBJ_SIZE_H - border_h){
                return true;
            }
            if (char_rect.y + CHAR_SIZE_H >= obj_rect.y + border_h && char_rect.y + CHAR_SIZE_H <= obj_rect.y + OBJ_SIZE_H - border_h){
                return true;
            }
        }
    }

    return false;
}
void init_stars(SDL_Renderer *renderer, vector<Star> &stars, vector<SDL_Rect> rect){
    for (size_t i = 0; i < rect.size(); i++){
        Star star_(renderer);
        star_.restart(rect[i]);
        stars.push_back(star_);
    }
    cout << "init " << stars.size() << " stars\n";
}
