#ifndef TEXTURE_OBJECT_H_INCLUDED
#define TEXTURE_OBJECT_H_INCLUDED

#include "SDL_utility.h"

using namespace std;

struct TextureObject
{
    SDL_Texture *texture_;
    SDL_Rect srcrect;
    SDL_Rect dstrect;

    TextureObject();
    void load_texture(const string &file_name,SDL_Renderer *renderer);
    void Set_dstRect(const int &x, const int &y, const int &w, const int &h);
    void Set_dstRect(const int &x, const int &y);
    void RenderTexture(SDL_Renderer *renderer);
    void Clean_Object();
};

#endif // TEXTURE_OBJECT_H_INCLUDED
