#ifndef ITEMS_H
#define ITEMS_H

#include<iostream>
#include<SDL2/SDL.h>
#include "bar.h"
using namespace std;
class items
{
public:
    const int step = 30;
    items();
    int x,y;
    SDL_Rect itemsRect;
    void updatePos();
};

#endif