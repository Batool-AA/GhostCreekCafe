#include<SDL.h>
using namespace std;
#pragma once
#include <vector>
#include "people.hpp"

class waiter_class: public people{ //sigleton class derived from people
protected:
    waiter_class(SDL_Rect src, SDL_Rect mover) : people(src, mover){};
public:

    void draw(SDL_Renderer* gRnderer, SDL_Texture* assets, SDL_Texture* as, SDL_Texture* s, SDL_Texture* o, SDL_Texture* food, SDL_Texture* money);
    void move(int x);
    static waiter_class& get(){ 
        static waiter_class instance({22,497,160,293}, {40, 400, 100, 100});
        return instance;
    }
    int get_move_x(){  //getter
        return moverRect.x;
    }
    int get_move_y(){ //getter
        return moverRect.y;
    }
};