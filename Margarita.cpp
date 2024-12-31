#pragma once
#include "Margarita.hpp"
#include <iostream>
#include "waiter.hpp"

void Margarita::move(waiter_class obj)
{
    moverRect.x = obj.get_move_x()+70;
    moverRect.y = obj.get_move_y() - 10;
    moverRect.w = 25;
    moverRect.h = 25;
}


void Margarita::set_mover(int x, int y, int w, int h){
    moverRect.x = x;
    moverRect.y = y;
    moverRect.w = w;
    moverRect.h = h;
}



int Margarita::check(vector<Menu*> countorder) //checks if there is an empty counter to display food
{
    bool counter_0 = false;
    bool counter_1 = false;
    bool counter_2 = false;
    bool counter_3 = false;
    for (int i = 0; i < countorder.size(); i++){
        if (countorder[i]->counter_number == 0){
            counter_0 = true;
        }
        if (counter_0 == true & countorder[i] -> counter_number == 1){
            counter_1 = true;
        }
        if (counter_0 == true & counter_1 == true & countorder[i] -> counter_number == 2){
            counter_2 = true;
        }
        if (counter_0 == true & counter_1 & counter_2 & countorder[i] -> counter_number == 3){
            counter_3 = true;
        }
    }

    if (counter_0 == false){
        moverRect = {50, 515, 50, 50};
        counter_number = 0;
        on_counter = true;
        return 1;
    }
    else if (counter_1 == false){
        moverRect = {150, 515, 50, 50};
        counter_number = 1;
        on_counter = true;
        return 1;
    }
    else if (counter_2 == false){
        moverRect = {250, 515, 50, 50};
        counter_number = 2;
        on_counter = true;
        return 1;
    }
    else if (counter_3 == false){
        moverRect = {350, 515, 50, 50};
        counter_number = 3;
        on_counter = true;
        return 1;
    }
    return 0;
} 

Margarita::Margarita (SDL_Rect scr, SDL_Rect move){ //constructor defining the srcrect and moverect
    srcRect = scr; 
    moverRect = move; 
}