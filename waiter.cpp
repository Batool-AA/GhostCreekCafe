#include<iostream>
#include "waiter.hpp"
#include <vector>
#include "SDL.h"
#include <ctime>
using namespace std;

//derived from people
void waiter_class::draw(SDL_Renderer* gRnderer, SDL_Texture* assets, SDL_Texture* as, SDL_Texture* s, SDL_Texture* o, SDL_Texture* food, SDL_Texture* money){
    SDL_RenderCopy(gRnderer, assets, &srcRect, &moverRect); 
}

void waiter_class :: move(int m){ //waiter movement through keyboard keys
    //left key
    if (m == 0){
        if (moverRect.y < 440 || moverRect.x > 390){
            if (srcRect.x == 22){
                srcRect = {24,900,164,293};
                moverRect.x -= 30;
            }
            else if (srcRect.x  == 24){
                moverRect.x -= 30;
                srcRect = {21,109,159,273};
            }
            else{
                moverRect.x -= 30;
                srcRect = {22,497,160,293};
            }
            if (moverRect.x <= -90){
                moverRect.x = 1000;
            }
        }
    }

    //right key
    if (m == 1){

        if (srcRect.x == 22){
                moverRect.x += 30;
                srcRect = {24,900,164,293};
            }
            else if (srcRect.x  == 24){
                moverRect.x += 30;
                srcRect = {21,109,159,273};
            }
            else{
                moverRect.x += 30;
                srcRect = {22,497,160,293};
            }
        if (moverRect.x >= 1020){
            moverRect.x = -70;
        }
    }

    //up key
    if (m == 2){
        if (srcRect.x == 22){
            srcRect = {24,900,164,293};
            moverRect.y -= 30;
        }
        else if (srcRect.x  == 24){
            srcRect = {21,109,159,273};
            moverRect.y -= 30;
        }
        else{
            srcRect = {22,497,160,293};
            moverRect.y -= 30;
        }
        if (moverRect.y <= -50){
            moverRect.y = 540;
        }
    }

    //down key
    if (m == 3){
        if (moverRect.y < 400 || moverRect.x > 390){
            if (srcRect.x == 22){
                srcRect = {24,900,164,293};
                moverRect.y += 30;
            }
            else if (srcRect.x  == 24){
                srcRect = {21,109,159,273};
                moverRect.y += 30;
            }
            else{
                srcRect = {22,497,160,293};
                moverRect.y += 30;
            }
            if (moverRect.y >= 590){
                moverRect.y = -10;
            }
        }
    } 
}
