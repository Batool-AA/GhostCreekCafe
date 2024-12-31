#include "Menu.hpp"

//getters
int Menu::get_srcx(){ 
    return srcRect.x;
}

int Menu::getsrcy(){
    return srcRect.y;
}

void Menu::draw(SDL_Renderer* gRnderer, SDL_Texture* assets){  //draws the object on screen
    SDL_RenderCopy(gRnderer,assets, &srcRect, &moverRect);
} 