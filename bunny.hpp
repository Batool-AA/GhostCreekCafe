#include<SDL.h>
using namespace std;
#pragma once
#include <vector>
#include "customer.hpp"

class vip : public customer_class{  //class derived from customer

public:
//prototypes of the functions
    void move(SDL_Rect& src, SDL_Rect& mover, int i);
    int sit(SDL_Rect & mover, int tbl, vector<customer_class*> cust_sit);
    vip(SDL_Rect src, SDL_Rect mover) : customer_class(src, mover){};
    friend bool operator==(SDL_Rect src1, SDL_Rect src2);
};