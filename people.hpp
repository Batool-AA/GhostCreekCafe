#pragma once
#include <SDL.h>

 //abstract people class
class people{
protected:
    SDL_Rect srcRect, moverRect;
public:
    people(SDL_Rect src, SDL_Rect mover): srcRect(src), moverRect(mover){};
    virtual void draw(SDL_Renderer* gRnderer, SDL_Texture* assets, SDL_Texture* asset, SDL_Texture* heart, SDL_Texture* o, SDL_Texture* food, SDL_Texture* money) = 0;
};