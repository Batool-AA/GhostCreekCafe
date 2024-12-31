#include<SDL.h>
using namespace std;
#pragma once
#include <vector>
#include "customer.hpp"

class non_vip : public customer_class{ //class inherited from customer

public:
//prototypes of all the functions of the class
    void move(SDL_Rect& src, SDL_Rect& mover, int i);   
    int sit(SDL_Rect & mover, int tbl, vector<customer_class*> cust_sit);
    non_vip(SDL_Rect src, SDL_Rect mover) : customer_class(src, mover){};
    friend bool operator==(SDL_Rect src1, SDL_Rect scrc2);
};

//bool operator==(SDL_Rect src1, SDL_Rect scrc2);

