#include "objectcreator.hpp"
#include <ctime>
using namespace std;

vector <Menu*> counter_orders; //keeps track of food items placed on counter



Menu* ObjectCreator :: GetOrder(int random) 
{
    //depending upon what random number is given, a new food item is created and pushed into a vector
    if (random == 0){
        Menu* item = new Salad({22,1615,115,83},{-100, -100, 50, 50});
        food_orders.push_back(item);
    }
    if (random == 2){
        Menu* item = new Pizza({9, 400, 193, 137},{-100, -100, 50, 50});
        food_orders.push_back(item);
    }
    if (random == 1){
        Menu* item = new CheeseCake({13, 1510, 130, 89},{-100, -100, 50, 50});
        food_orders.push_back(item);
    }
    if (random == 3)
    {
        Menu* item = new Margarita({24, 1220, 92, 172},{-100, -100, 50, 50});
        food_orders.push_back(item);
    }
    if (random == 4)
    {
        Menu* item = new Hotchoc({7, 1018, 136, 116},{-100, -100, 50, 50});
        food_orders.push_back(item);
    }
}


void ObjectCreator :: draw(SDL_Renderer* gRnderer, SDL_Texture* assets){
    for (int i = 0; i < food_orders.size(); i++){ //iterates over food_orders and if a counter is empty, it pushes the food into counter_orders and erased from food_orders
        food_orders[i] -> counter += 1;
        if (food_orders[i] -> counter >= 20){  // Brings food on the counter
            if (food_orders[i] -> check(counter_orders) == 1){
                counter_orders.push_back(food_orders[i]);
                food_orders.erase(food_orders.begin()+i);
            }
        }
    }

    for (int i = 0; i < counter_orders.size(); i++){  //draws the food items on counter
        counter_orders[i] -> draw(gRnderer, assets);
        if (counter_orders[i]->delivered == true){ //once it is delivered, a counter starts, which on reaching 40, removes the food from counter_orders
            counter_orders[i] -> counter_delivered += 1;
            if (counter_orders[i] -> counter_delivered >= 80){ // Deletes the food from the table
                delete counter_orders[i];
                counter_orders.erase(counter_orders.begin()+i);
            }
        }
    }
}


Menu* ObjectCreator :: clicked_on(int counter_no, waiter_class obj){
    for (int i = 0; i < counter_orders.size() ; i++){   //return the item that has been clicked on
        if ((counter_orders[i] -> counter_number) == counter_no){
            return counter_orders[i];
        }
    }
}

ObjectCreator::~ObjectCreator(){
    for (int i=0; i<counter_orders.size();i++){
        delete counter_orders[i];
    }
    for(int i=0; i<food_orders.size(); i++){
        delete food_orders[i];
    }
}

void ObjectCreator::delete_food(){
    for (int i = 0; i < counter_orders.size(); i++){
        if (counter_orders[i] -> counter_number == 5 & counter_orders[i] -> on_counter == true){
            delete counter_orders[i];
            counter_orders.erase(counter_orders.begin()+i);
            break;
        }
    }
}