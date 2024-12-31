#include<iostream>
#include "customer.hpp"
#include <vector>
#include "SDL.h"
#include <cmath>
#include <ctime>
#include "bean.hpp"
#include "objectcreator.hpp"
#include "bunny.hpp"
using namespace std;

ObjectCreator objectcreator;

//keeps a track of how many customers came
int num_customers = 0;
//a counter to create a new customer
int counter = 0;
//keeping track of how many customers leave
int cust_left = 0;
//the three hearts representing waiter's/user's lives
SDL_Rect heart = {9, 22, 106, 89}; //src of the heart
SDL_Rect heart_1 = {0, 0, 50, 50}; //moverrect of heart 1
SDL_Rect heart_2 = {60, 0, 50, 50}; //moverrect of heart 2
SDL_Rect heart_3 = {120, 0, 50, 50}; //moverrect of heart 3

//keeping track of money collected from tables
int money_collection = 0;

void customer_class::draw(SDL_Renderer* gRnderer, SDL_Texture* assets, SDL_Texture* sit, SDL_Texture* h, SDL_Texture* o, SDL_Texture* food, SDL_Texture* money){
    counter += 1;
    if (customer_vector.size() < 3 & counter == 1 & num_customers < 10){ //a customer appears after count is 1 when the vector has no customer
        srand(time(0));
        int random = rand() % 10;
        if (random >= 3){
            customer_class* custom = new non_vip ({34, 16, 257, 495}, {-40, 250, 90, 90});
            customer_vector.push_back(custom);
            num_customers += 1;
        }
        else{
            customer_class* custom = new vip ({87, 3132, 208, 452}, {-40, 250, 90, 90});
            customer_vector.push_back(custom);
            num_customers += 1;
        }
    }
    else if (customer_vector.size() < 2 & counter == 50 & num_customers < 10){  //next customer appears when count is 50 and vector has 1 customer
        srand(time(0));
        int random = rand() % 10;
        if (random >= 3){
            customer_class* custom = new non_vip ({34, 16, 257, 495}, {-40, 250, 90, 90});
            customer_vector.push_back(custom);
            num_customers += 1;
        }
        else{
            customer_class* custom = new vip ({87, 3132, 208, 452}, {-40, 250, 90, 90});
            customer_vector.push_back(custom);
            num_customers += 1;
        }
    }

    else if (customer_vector.size() < 1 & counter == 100 & num_customers < 10){  //another customer appears when counter reaches 100 and the vector has 2 customers
        srand(time(0));
        int random = rand() % 10;
        if (random >= 3){
            customer_class* custom = new non_vip ({34, 16, 257, 495}, {-40, 250, 90, 90});
            customer_vector.push_back(custom);
            num_customers += 1;
        }
        else{
            customer_class* custom = new vip ({87, 3132, 208, 452}, {-40, 250, 90, 90});
            customer_vector.push_back(custom);
            num_customers += 1;
        }
    }


    for (int i = 0; i < customer_vector.size(); i++){  
        SDL_RenderCopy(gRnderer, assets, &customer_vector[i] -> srcRect, &customer_vector[i] -> moverRect);  //drawing the customers

        customer_vector[i]->move(customer_vector[i]->srcRect, customer_vector[i]->moverRect, i); //calling the move function of each customer

        if (customer_vector[i] -> patience <= 100){ //if patience is less than 100, 3 hearts appear
            customer_vector[i] -> heart_mover = {customer_vector[i] -> moverRect.x, customer_vector[i] -> moverRect.y - 30, 20, 20};
            SDL_RenderCopy(gRnderer, h, &customer_vector[i] -> heart_src, &customer_vector[i] -> heart_mover);   
            customer_vector[i] -> heart_mover = {customer_vector[i] -> moverRect.x + 20, customer_vector[i] -> moverRect.y - 30, 20, 20};
            SDL_RenderCopy(gRnderer, h, &customer_vector[i] -> heart_src, &customer_vector[i] -> heart_mover); 
            customer_vector[i] -> heart_mover = {customer_vector[i] -> moverRect.x + 40, customer_vector[i] -> moverRect.y - 30, 20, 20};
            SDL_RenderCopy(gRnderer, h, &customer_vector[i] -> heart_src, &customer_vector[i] -> heart_mover); 
        }

        else if(customer_vector[i] -> patience <= 200){  //if patience is less than 200, 2 hearts appear
            customer_vector[i] -> heart_mover = {customer_vector[i] -> moverRect.x + 20, customer_vector[i] -> moverRect.y - 30, 20, 20};
            SDL_RenderCopy(gRnderer, h, &customer_vector[i] -> heart_src, &customer_vector[i] -> heart_mover); 
            customer_vector[i] -> heart_mover = {customer_vector[i] -> moverRect.x + 40, customer_vector[i] -> moverRect.y - 30, 20, 20};
            SDL_RenderCopy(gRnderer, h, &customer_vector[i] -> heart_src, &customer_vector[i] -> heart_mover); 
        }

        else if (customer_vector[i] -> patience <= 300){ //if patience is less than 300, 1 heart appears
            customer_vector[i] -> heart_mover = {customer_vector[i] -> moverRect.x + 40, customer_vector[i] -> moverRect.y - 30, 20, 20};
            SDL_RenderCopy(gRnderer, h, &customer_vector[i] -> heart_src, &customer_vector[i] -> heart_mover); 
        }

        if (customer_vector[i] -> patience >= 300){  //if patience exceeds 300, the customer leaves
            delete customer_vector[i];
            customer_vector.erase(customer_vector.begin()+i);  //customer is erased from the vector
            counter = 0;   //a space is emptied in the customer vector so the count is changed back to 0
            cust_left += 1;    //patience reaches 300, which means a customer leaves
        }
    }

    for (int i = 0; i < customer_sitting.size(); i++){
        SDL_RenderCopy(gRnderer, sit, &customer_sitting[i] -> srcRect, &customer_sitting[i] -> moverRect);  //drawing the customer

        if (customer_sitting[i] -> order_given == true){ //if the customer is given the food, a counter starts
            customer_sitting[i] -> counter_food += 1;
        }

        if (customer_sitting[i] -> counter_food >= 80){ //when this counter reaches 80, the customer disappears
            customer_sitting[i] -> moverRect.x = -100; //customer disappears from the screen
            customer_sitting[i] -> moverRect.y = -100;
            SDL_RenderCopy(gRnderer, money, &customer_sitting[i] -> money_src, &customer_sitting[i] -> money_mover); //drawing its money
        }

        if (customer_sitting[i] -> money_collected == true){
            delete customer_sitting[i];
            customer_sitting.erase(customer_sitting.begin()+i);
       }

        if (customer_sitting[i] -> order_given == false){ //if the order is not given
            customer_sitting[i] -> patience += 1; //the patience counter increases

            if (customer_sitting[i] -> patience == 50){
                customer_sitting[i] -> order_src = customer_sitting[i] -> generate_food(); //after 50 frames, a random order is chosen
            }

            if (customer_sitting[i] -> patience >= 40){  // 40 frames after the customer sits
                customer_sitting[i] -> ob_mover = {customer_sitting[i] -> moverRect.x-50, customer_sitting[i] -> moverRect.y - 70, 70, 70};
                SDL_RenderCopy(gRnderer, o, &customer_sitting[i] -> ob_src, &customer_sitting[i] -> ob_mover);   //order bubble appears

                customer_sitting[i] -> order_mover = {customer_sitting[i] -> ob_mover.x + 25, customer_sitting[i] -> ob_mover.y + 7, 35, 35};
                SDL_RenderCopy(gRnderer, food, &customer_sitting[i] -> order_src, &customer_sitting[i] -> order_mover); //food order appears in the bubble

                objectcreator.draw(gRnderer, food); //a function is called which is responsible for making the food appear on counter
            }

            if (customer_sitting[i] -> patience <= 100){ //once the customer sits, patience below 100 resembles 3 hearts
                customer_sitting[i] -> heart_mover = {customer_sitting[i] -> moverRect.x, customer_sitting[i] -> moverRect.y - 30, 20, 20};
                SDL_RenderCopy(gRnderer, h, &customer_sitting[i] -> heart_src, &customer_sitting[i] -> heart_mover);   
                customer_sitting[i] -> heart_mover = {customer_sitting[i] -> moverRect.x + 20, customer_sitting[i] -> moverRect.y - 30, 20, 20};
                SDL_RenderCopy(gRnderer, h, &customer_sitting[i] -> heart_src, &customer_sitting[i] -> heart_mover); 
                customer_sitting[i] -> heart_mover = {customer_sitting[i] -> moverRect.x + 40, customer_sitting[i] -> moverRect.y - 30, 20, 20};
                SDL_RenderCopy(gRnderer, h, &customer_sitting[i] -> heart_src, &customer_sitting[i] -> heart_mover); 
            }

            else if(customer_sitting[i] -> patience <= 200){   //patience below 200 and greater than 100 is 2 hearts
                customer_sitting[i] -> heart_mover = {customer_sitting[i] -> moverRect.x + 20, customer_sitting[i] -> moverRect.y - 30, 20, 20};
                SDL_RenderCopy(gRnderer, h, &customer_sitting[i] -> heart_src, &customer_sitting[i] -> heart_mover); 
                customer_sitting[i] -> heart_mover = {customer_sitting[i] -> moverRect.x + 40, customer_sitting[i] -> moverRect.y - 30, 20, 20};
                SDL_RenderCopy(gRnderer, h, &customer_sitting[i] -> heart_src, &customer_sitting[i] -> heart_mover);
            }

            else if (customer_sitting[i] -> patience <= 300){ //patience below 300 and greater that 200 is 1 heart
                customer_sitting[i] -> heart_mover = {customer_sitting[i] -> moverRect.x + 40, customer_sitting[i] -> moverRect.y - 30, 20, 20};
                SDL_RenderCopy(gRnderer, h, &customer_sitting[i] -> heart_src, &customer_sitting[i] -> heart_mover);
            }

            if (customer_sitting[i] -> patience >= 300){ //once the patience reaches 300, the customer leaves
                cust_left += 1; //increment is the number of customers left
                delete customer_sitting[i];
                customer_sitting.erase(customer_sitting.begin()+i);   //customer removed from vector
            }
        }
    }
    
    if (cust_left == 0){ //if no customer is left, player has 3 lives, 3 hearts remain
        SDL_RenderCopy(gRnderer, h, &heart, &heart_1); 
        SDL_RenderCopy(gRnderer, h, &heart, &heart_2);
        SDL_RenderCopy(gRnderer, h, &heart, &heart_3);
    } 
    else if (cust_left == 1){  //if one customer leaves, one life is gone, 2 hearts remain
        SDL_RenderCopy(gRnderer, h, &heart, &heart_1); 
        SDL_RenderCopy(gRnderer, h, &heart, &heart_2);
    }
    else if (cust_left == 2){  //if 2 customers leave, 2 lives gone, one heart remains
        SDL_RenderCopy(gRnderer, h, &heart, &heart_1); 
    }

    if (money_collection >= 40){   //when the waiter gets 40 points, one life comes back
        if (cust_left == 1){   
            cust_left = 0;
        }
        else if (cust_left == 2){
            cust_left = 1;
        }
        money_collection = 0;
    }
}

void customer_class :: clicked(int tbl){ //making the customers sit, takes the table number as an arguement
    if (customer_vector[0] -> sit(customer_vector[0] -> moverRect, tbl, customer_sitting) == 0){  //if the sit function returns 0, the customer is assigned a table
        if (customer_vector[0] -> srcRect.x == 87){
            customer_vector[0] -> srcRect = {11, 293, 165, 193};
        }
        else if (customer_vector[0] -> srcRect.x == 34){
            customer_vector[0] -> srcRect = {195, 33, 153, 212};
        }
        customer_vector[0] -> table_number = tbl;
        customer_sitting.push_back(customer_vector[0]); //the customer is pushed in another vector and removed from the [revious one]
        customer_vector.erase(customer_vector.begin());
        counter = 0; //the count is restored to 0 to trigger the incoming of a new customer
    }
}

bool customer_class :: lose(){ //function return true/false in game which thn leads to a change in screen
    if (cust_left == 3){ //if three customers leave, the game is over
        return true;
    }
    else{
        return false;
    }
}

bool customer_class :: win(){ //function return true/false in game which thn leads to a change in screen
    if (num_customers >= 10 & customer_sitting.size() == 0 & customer_vector.size() == 0){ //if all 10 customers come and leave, the player wins
        return true;
    }
    else{
        return false;
    }
}

SDL_Rect customer_class::generate_food(){  //this function is called in customer's draw which generates a random food order for each customer once they sit on the tables
    srand(time(0));
    int random = rand()%5;
    if (random == 0){
        objectcreator.GetOrder(random); //this function takes the random number and creates a new item corresponding to the number which appears on the counter some frames later
        return {22, 1615, 115, 83};
    }
    else if (random == 1){
        objectcreator.GetOrder(random); //this function takes the random number and creates a new item corresponding to the number which appears on the counter some frames later
        return {13, 1510, 130, 89};
    }
    else if (random == 2){
        objectcreator.GetOrder(random); //this function takes the random number and creates a new item corresponding to the number which appears on the counter some frames later
        return {9, 400, 193, 137};
    }
    else if (random == 3){
        objectcreator.GetOrder(random); //this function takes the random number and creates a new item corresponding to the number which appears on the counter some frames later
        return {24, 1220, 92, 172};
    }
    else if (random == 4){
        objectcreator.GetOrder(random); //this function takes the random number and creates a new item corresponding to the number which appears on the counter some frames later
        return {7, 1018, 136, 116};
    }
}

bool customer_class::comparefood(Menu* order, int tbl) //the function is called when the waiter tries to deliver some food, it checks the src of the food being delivered and the one in the order bubble
{
    for (int i = 0; i < customer_sitting.size(); i++){
        if (customer_sitting[i] -> table_number == tbl){
            if ((order -> get_srcx() == customer_sitting[i]->order_src.x) & (order -> getsrcy() == customer_sitting[i]->order_src.y)){
                customer_sitting[i] -> order_given = true;
                return true;
            }
        }
    }
}

void customer_class :: money_pickup(int tbl){ //based on the customer, a different number is added to the money/score
    for (int i = 0; i < customer_sitting.size(); i++){
        if (customer_sitting[i] -> table_number == tbl & customer_sitting[i]->order_given==true){
            customer_sitting[i] -> money_collected = true;
            if (customer_sitting[i] -> srcRect.x == 195){ //bean, non-vip
                money_collection += 10;
            } 
            else{
                money_collection += 20;
            }
        }
    }
}
bool operator==(SDL_Rect src1, SDL_Rect src2){ //operator overloading
    bool comp=false;
    if((src1.x==src2.x) && (src1.y==src2.y) && (src1.w==src2.w) && (src1.h==src2.h)){
            comp=true;
    }
    return comp;
}
customer_class::~customer_class(){
    for(int i=0; i<customer_sitting.size();i++){
        delete customer_sitting[i];
    }
    for(int i=0; i<customer_vector.size();i++){
        delete customer_vector[i];
    }
    customer_sitting.clear();
    customer_vector.clear();
}