#pragma once
#include <iostream>
#include <SDL.h>
#include "waiter.hpp"

class Menu{
protected:
    SDL_Rect srcRect, moverRect;
public:
    virtual int check(vector<Menu*>) = 0;
    void draw(SDL_Renderer* gRnderer, SDL_Texture* assets);
    virtual void move(waiter_class obj) = 0; //a virtual function that is being redifined in every derived class
    virtual void set_mover(int x, int y, int w, int h) = 0;
    int get_srcx();
    int getsrcy();
    bool delivered = false;
    bool on_counter = false;
    int counter = 0; //the counter starts when a new item is created but the item is not drawn until the counter reaches a certain valie
    int counter_delivered = 0; //the counter starts when food is delivered to customer, after some time the food disappears
    int counter_number = 5; //each food has a counter number on  which it appears
};

