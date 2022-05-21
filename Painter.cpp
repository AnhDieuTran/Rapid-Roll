#include "painter.h"
#include "utils.h"

using namespace std;

Painter::Painter(SDL_Window* window, SDL_Renderer* renderer_) : renderer(renderer_)
{
    SDL_RenderGetLogicalSize(renderer, &width, &height);
    if (width == 0 && height == 0)
        SDL_GetWindowSize(window, &width, &height);

    setPosition(width/2, height/2);
    setAngle(0);
    setColor(BLUE_COLOR);
    clearWithBgColor(BLUE_COLOR);
}

void Painter::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Painter::setAngle(float angle)
{
    this->angle = angle - floor(angle/360)*360;
}

void Painter::setColor(SDL_Color color)
{
    this->color = color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
}

void Painter::clearWithBgColor(SDL_Color bgColor)
{
    SDL_Color curColor = color;
    setColor(bgColor);
    SDL_RenderClear(renderer);
    setColor(curColor);
}

void Painter::moveForward(float length)
{
    float prevX = x, prevY = y;
    jumpForward(length);
    SDL_RenderDrawLine(renderer, (int)prevX, (int)prevY, (int)x, (int)y);
}

void Painter::jumpForward(float length)
{
    float rad = (angle / 180) * M_PI;
    x += (cos(rad) * length);
    y -= (sin(rad) * length);
}

void Painter::setRandomColor()
{
    Uint8 r = rand() % 256;
    Uint8 g = rand() % 256;
    Uint8 b = rand() % 256;
    SDL_Color color = {r, g, b};
    setColor(color);
}

void Painter::createCircle(float radius)
{
    double rad = (angle / 180) * M_PI;
    int centerX = x + cos(rad) * radius;
    int centerY = y - sin(rad) * radius;

    int dx = radius;
    int dy = 0;
    int err = 0;
    for (int i = 0; i <= radius; ++i) {
        int dx = i;
        int dy = 0;
        int err = 0;
        while (dx >= dy)
        {
            SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            SDL_RenderDrawPoint(renderer, centerX + dy, centerY + dx);
            SDL_RenderDrawPoint(renderer, centerX - dy, centerY + dx);
            SDL_RenderDrawPoint(renderer, centerX - dx, centerY + dy);
            SDL_RenderDrawPoint(renderer, centerX - dx, centerY - dy);
            SDL_RenderDrawPoint(renderer, centerX - dy, centerY - dx);
            SDL_RenderDrawPoint(renderer, centerX + dy, centerY - dx);
            SDL_RenderDrawPoint(renderer, centerX + dx, centerY - dy);

            if (err <= 0)
            {
                dy += 1;
                err += 2*dy + 1;
            }
            if (err > 0)
            {
                dx -= 1;
                err -= 2*dx + 1;
            }
        }
    }   
}

// Vẽ ảnh
bool Painter::createImage( SDL_Texture* texture )
{
    if( texture == NULL ) return false;
    SDL_RenderCopy( renderer, texture, NULL, NULL );
    return true;
}

// Vẽ lại nền màn hình chính
void refreshScreen(SDL_Window* &window, SDL_Renderer* &renderer, Painter painter, SDL_Texture* &background,SDL_Texture* &_back, SDL_Texture* &heart, int live)
{
    renderTexture(background, renderer, 0, 0, 420, 680);
    renderTexture(_back, renderer, 0, 0);
    for (int i = 1; i <= live; i++) {
        renderTexture(heart, renderer, 10, 50 + i*20, 20,20);
    }
}

// Vẽ số lên renderer ở toạ độ x, y
void printNumber(SDL_Renderer* renderer, TTF_Font* font, int number, int x, int y)
{
    SDL_Surface* num_cur = TTF_RenderText_Solid(font, numberToString(number).c_str(), BLACK_COLOR);
    SDL_Texture* Num_render = SDL_CreateTextureFromSurface(renderer, num_cur);
    renderTexture(Num_render, renderer, x, y);
}

// Vẽ chữ lên renderer ở toạ độ x, y
void printText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, std::string str, int x, int y){
    SDL_Surface* num_cur = TTF_RenderText_Solid(font, str.c_str(), color);
    SDL_Texture* Num_render = SDL_CreateTextureFromSurface(renderer, num_cur);
    renderTexture(Num_render, renderer, x, y);
}

// Vẽ chữ lên renderer ở toạ độ x, y nhưng có thêm chiều rộng và độ cao cho trước
void printText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, std::string str, int x, int y, int w, int h){
    SDL_Surface* num_cur = TTF_RenderText_Solid(font, str.c_str(), color);
    SDL_Texture* Num_render = SDL_CreateTextureFromSurface(renderer, num_cur);
    renderTexture(Num_render, renderer, x, y, w, h);
}

// Xoá bỏ background
SDL_Texture* removeBackground(SDL_Renderer* renderer, std::string path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface ->format,255,255,255));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    return texture;
}