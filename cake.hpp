#pragma once
#include "Menu.hpp"


class CheeseCake : public Menu{ //inherited from Menu class

public:
    void move(waiter_class obj);  
    int check(vector<Menu*>) ;
    void set_mover(int x, int y, int w, int h);
    CheeseCake(SDL_Rect srcRect, SDL_Rect moverRect); //constructor that takes coordinates of 
};

