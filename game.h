#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>

#include "Painter.h"
#include "utils.h"
#include "bar.h"
#include "items.h"

using namespace std;

//**********************************************//

int playGame(SDL_Window *window, SDL_Renderer *renderer, int arrScore[], int fps);

int showMenu(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font);

bool checkFocus(const int& x, const int& y, SDL_Rect rect);

int showLevel(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font);

int playAgain(SDL_Renderer* renderer, TTF_Font* font);

int mouse_button_down(SDL_Event m_event, int xm, int ym, int numsOfChoice,SDL_Rect pos_arr[]);

void mouse_motion(SDL_Event m_event, int xm, int ym, int numsOfChoice,SDL_Rect pos_arr[], bool selected[], SDL_Color color[]);

void remove(SDL_Rect &rect);

#endif