#include<SDL.h>
using namespace std;
#include <vector>
#include "bunny.hpp"
#include <iostream>



void vip::move(SDL_Rect& src, SDL_Rect& mover, int i){ //moving the bunny
    SDL_Rect state1={135, 2633, 223, 441};
    SDL_Rect state2={87, 3132, 208, 452}; 
    if (i == 2 && mover.x < 0 & mover.y > 200 & mover.y < 300){ //third customer stops at 0
        mover.x += 10;
        if ((src==state1)==true ){
            src = state2;  
        }
        else if ((src==state2)==true ){
            src = state1;
        }
    }

    else if (i == 1 && mover.x < 100 & mover.y > 200 & mover.y < 300){ //second customer stops at 100
        mover.x += 10;
       if ((src==state1)==true ){
            src= state2;            
        }
        else if ((src==state2)==true ){
            src = state1;
        }
    }

    else if (i == 0 && mover.x < 200 & mover.y > 200 & mover.y < 300){ //first customer stops at 200
        mover.x += 10;
       if ((src==state1)==true ){
            src= state2;            
        }
        else if ((src==state2)==true ){
            src = state1;
        }
    }

    if ((i == 0 & mover.x >= 200) || (i == 1 & mover.x >= 100) || (i == 2 & mover.x >= 0)){
        src = state2;
        patience += 1; //the customer has reached its place in the queue, now the patience increases
    }
}

int vip::sit(SDL_Rect & mover, int tbl, vector<customer_class*> cust_sit){//the function makes sure that the u=customer is sat on a table which is unoccupied 
    for (int i = 0; i < cust_sit.size(); i++){
        if (cust_sit[i]->table_number == tbl){
            return 1; //if that table is occupied, the function returns 1 ie the customer will not move
        }
    }

    //if the desired table is unoccupied, the moverrect of the customer are changed,patience is reloaded and money is assigned its location
    if (tbl == 1){
        mover.x = 300;
        mover.y = 140;
        patience = 0;
        money_mover = {200, 150, 50, 50};
        return 0;
    }
    else if (tbl == 2){
        mover.x = 670;
        mover.y = 160;
        patience = 0;
        money_mover = {580, 160, 50, 50};
        return 0;
    }
    else if (tbl == 3){
        mover.x = 448;
        mover.y = 347;
        patience = 0;
        money_mover = {350, 340, 50, 50};
        return 0;
    }
    else if (tbl == 4){
        mover.x = 840;
        mover.y = 360;
        patience = 0;
        money_mover = {700, 350, 50, 50};
        return 0;
    }
    return 0;
}

