#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "SDL_utility.h"
#include "Texture_object.h"
#include "Game_Map.h"
#include "Character.h"

using namespace std;

#define CHAR_SIZE_W   50
#define CHAR_SIZE_H   50

struct Enemy
{
    TextureObject char_frame[7];
};

#endif // ENEMY_H_INCLUDED
