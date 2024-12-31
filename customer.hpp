#include<SDL.h>
#pragma once
using namespace std;
#include <vector>
#include "people.hpp"
#include "Menu.hpp"

class customer_class: public people{ //class derived from people
protected:
    int patience = 0; //each customer has its patience counter

    SDL_Rect heart_src = {9, 22, 106, 89};  //each customer has its own hearts
    SDL_Rect heart_mover = {};

    SDL_Rect ob_src = {15, 0, 208, 212}; //orderbubble of each customer
    SDL_Rect ob_mover = {};

    SDL_Rect order_src = {};  //the order that is randomly chosen for each customer
    SDL_Rect order_mover = {};

    bool order_given = false; //bool to keep track of whether the food is delivered or not
    int counter_food = 0;  //the counter triggered when the food is given, when it reaches 40, the customer leaves
    
    vector <customer_class*> customer_vector; //a vector that has customers standing in quueue
    vector <customer_class*> customer_sitting; //vector having customers sitting on tables

    SDL_Rect money_src = {4, 20, 90, 47}; //money that each customer leaves behind
    SDL_Rect money_mover = {};

    bool money_collected = false;

public:
//prototypes of all the functions
    void draw(SDL_Renderer* gRnderer, SDL_Texture* assets, SDL_Texture* sit, SDL_Texture* hearts, SDL_Texture* o, SDL_Texture* food, SDL_Texture* money);
    virtual void move(SDL_Rect& src, SDL_Rect& mover, int i) = 0;
    virtual int sit(SDL_Rect& mover, int, vector<customer_class*>) = 0;
    void clicked(int);
    customer_class(SDL_Rect src, SDL_Rect mover) : people(src, mover){};
    int table_number = 0; //each customer has a table number
    bool lose();
    bool win();
    SDL_Rect generate_food();
    bool comparefood(Menu*, int);
    void money_pickup(int);
    friend bool operator==(SDL_Rect src1, SDL_Rect src2) ;
    virtual ~customer_class();
};
bool operator==(SDL_Rect src1, SDL_Rect src2) ;//operator overloading
   

