#pragma once
#include "Menu.hpp"

class Pizza:public Menu{  //inherited from Menu
public:
    void move(waiter_class obj);  
    int check(vector<Menu*>);
    void set_mover(int x, int y, int w, int h);
    Pizza(SDL_Rect srcRect, SDL_Rect moverRect);
};