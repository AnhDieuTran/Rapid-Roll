#include <SDL2/SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "game.h"

using namespace std;

//**********************************************************

int main(int argc, char* argv[]) {

    SDL_Window *window;
	SDL_Renderer *renderer;
	
	initSDL(window, renderer);

    SDL_Texture* menu = loadTexture("image/menu.jpg", renderer);
    SDL_Texture* level = loadTexture("image/level1.jpg", renderer);

    TTF_Init();
    TTF_Font* font1 = NULL;
    font1 = TTF_OpenFont("font/COOPBL.TTF", 32);
    TTF_Font* font2 = NULL;
    font2 = TTF_OpenFont("font/COOPBL.TTF", 24);

    int fps;
    int arrScore[5] = {0};

    int ret_menu = showMenu(renderer, menu, font1);
    if (ret_menu == 1) {
        return 0;
    } else if (ret_menu == 0) {    
        int ret_level = showLevel(renderer, level, font2);
        if (ret_level == 0) fps = 10;
        else if (ret_level == 1) fps = 20;
        else if (ret_level == 2) fps = 30;
    }

    int play = 0;
    
    do 
    {
        play = playGame(window, renderer, arrScore, fps);

    } while (play == 0);

    SDL_DestroyTexture(menu);
    SDL_DestroyTexture(level);

    quitSDL(window, renderer);


    return 0;
}
