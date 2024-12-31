#include "cake.hpp"
#pragma once
#include "Menu.hpp"
#include "Pizza.hpp"
#include "Salad.hpp"
#include "Margarita.hpp"
#include "hotchoc.hpp"
#include <vector>
#include "waiter.hpp"

class ObjectCreator{
//defining attributes and function prototypes
protected:
    vector <Menu*> food_orders;
    Menu* item;
public:
    Menu* GetOrder(int);  
    Menu* clicked_on(int x, waiter_class);
    void draw(SDL_Renderer* gRnderer, SDL_Texture* assets);
    ~ObjectCreator();
    void delete_food();
}; 