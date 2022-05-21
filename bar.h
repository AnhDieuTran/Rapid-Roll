#ifndef BAR_H
#define BAR_H
#include<iostream>
#include<SDL2/SDL.h>
#include <time.h>

using namespace std;
class bar
{
public:
    const int step = 30;
    bar();
    int x,y;
    SDL_Rect barRect;
    void updatePos();
};
#endif