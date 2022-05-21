#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include <time.h>

const int SCREEN_WIDTH = 420;
const int SCREEN_HEIGHT = 680;
const int CHOICE_MENU = 2;
const int LEVEL = 3;
const std::string WINDOW_TITLE = "Rapid Roll";


void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) ;

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

SDL_Texture* loadTexture(std::string file, SDL_Renderer *ren);

// Hàm đưa texture ra renderer tại toạ độ (x,y) và giữ nguyên kích cỡ ban đầu của ảnh
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

// Hàm (giống trên nhưng khác tham số)
// đưa texture ra renderer tại toạ độ (x,y) với kích cỡ rộng (w) và cao (h) cho trước.
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

std::string numberToString(int Number);

#endif