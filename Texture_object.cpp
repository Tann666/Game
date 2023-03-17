#include "Texture_object.h"

TextureObject::TextureObject()
{
    texture_ = NULL;
    srcrect = {0,0,0,0};
    dstrect = {0,0,0,0};
}

void TextureObject::load_texture(const string &file_name,SDL_Renderer *renderer)
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = IMG_Load(file_name.c_str());
    if (surface != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
        if (texture == nullptr) logSDLError(cout,"CreateTextureFromSurface",true);
    }
    else logSDLError(cout,"IMG_load",true);
    texture_ = texture;
    SDL_QueryTexture(texture_,NULL,NULL,&srcrect.w,&srcrect.h);
}
void TextureObject::Set_dstRect(const int &x, const int &y, const int &w, const int &h)
{
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = w;
    dstrect.h = h;
}
void TextureObject::Set_dstRect(const int &x, const int &y)
{
    dstrect.x = x;
    dstrect.y = y;
}
void TextureObject::RenderTexture(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture_,&srcrect,&dstrect);
}

void TextureObject::Clean_Object()
{
    SDL_DestroyTexture(texture_);
    srcrect = {0,0,0,0};
    dstrect = {0,0,0,0};
}
