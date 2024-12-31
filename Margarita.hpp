#pragma once
#include "Menu.hpp"

class Margarita:public Menu{  //inherited from Menu
public:
    void move(waiter_class obj);  
    int check(vector<Menu*>);
    void set_mover(int x, int y, int w, int h);
    Margarita(SDL_Rect srcRect, SDL_Rect moverRect);
};
