#include "game.hpp"
#include "waiter.hpp"
#include "customer.hpp"
#include "bean.hpp"
#pragma once
#include "objectcreator.hpp"


bool Game::init()
{
	//Initialization flag
	bool success = true;
	 if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "HU Mania", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }

			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;
	customers = loadTexture("anything.sprite.png");
	waiter = loadTexture("waitersprite7up.png");
	food_img = loadTexture("sprite.sprite.png");
	money = loadTexture("money.png");
	orderbubble = loadTexture("Order Cloud.png");
    gTexture = loadTexture("cafefinal.png");
	temp_bg = loadTexture("mainscreen.png");
	temp_ins = loadTexture("ins.png");
	lose = loadTexture("You Lose! (1).png");
	win = loadTexture("You win! (1).png");
	bean_sit = loadTexture("sitting.png");
	heart = loadTexture("life1.png");


	//Load music
    gMusic = Mix_LoadMUS( "pinkpan.mp3" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

	if(waiter==NULL || gTexture==NULL || food_img == NULL || customers==NULL || money==NULL || orderbubble==NULL || temp_bg==NULL || temp_ins==NULL || lose==NULL || win==NULL || bean_sit==NULL ||heart==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(waiter);
	waiter=NULL;
	SDL_DestroyTexture(gTexture);
	SDL_DestroyTexture(food_img);
	SDL_DestroyTexture(customers);
	SDL_DestroyTexture(money);
	SDL_DestroyTexture(orderbubble);
	SDL_DestroyTexture(temp_bg);
	SDL_DestroyTexture(temp_ins);
	SDL_DestroyTexture(lose);
	SDL_DestroyTexture(win);
	SDL_DestroyTexture(bean_sit);
	SDL_DestroyTexture(heart);
	food_img=NULL;	
	gTexture=NULL;
	customers=NULL;
	money=NULL;
	orderbubble=NULL;
	temp_bg=NULL;
	temp_ins=NULL;
	lose=NULL;
	win=NULL;
	bean_sit=NULL;
	heart=NULL;
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	Mix_FreeMusic( gMusic );
    gMusic = NULL;


	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}
void Game::run( )
{
	//defining different bools to control screen switching
	bool play = false;
	bool quit = false;
	bool instructions = false;
	bool w_b = false;
	bool l_b = false;

	bool moneypick= false;
	bool delete_food =false;
	bool picked_f = false; //checking if the food is picked
	bool clicked_cust = false; //checkin if the customer is clicked
	//music
	Mix_PlayMusic( gMusic, -1 );
	int counter_number = 5;

	Menu* picked; //creating a dynamic object of class menu
	ObjectCreator obj; //creating object of ObjectCreator
	SDL_Event e;
	waiter_class &w=waiter_class::get(); //creating object of class waiter
	customer_class* cust = new non_vip({},{}); //creating vip class object

	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){ //keyboard input 
				switch (e.key.keysym.sym){
					//for waiter's movement: calls a function which changes the moverrect
					case SDLK_LEFT: 
						w.move(0);
						break;
					case SDLK_RIGHT:
						w.move(1);
						break;
					case SDLK_UP:
						w.move(2);
						break;
					case SDLK_DOWN:
						w.move(3);
						break;
					//clicking p to play
					case SDLK_p:
						play = true;
						instructions = false;
						break;
					//clicking i for instructions
					case SDLK_i:
						instructions = true;
						break;
					//clicking b for back
					case SDLK_b:
						instructions = false;
					case SDLK_d:   // Press 'd' to delete the food present on the counter
						delete_food  = true;
					//clicking 1, 2, 3, 4 to assign tables to customers
					case SDLK_1:
						if (clicked_cust == true){
							clicked_cust = false;
							cust -> clicked(1);
							break;
						}
					case SDLK_2:
						if (clicked_cust == true){
							clicked_cust = false;
							cust -> clicked(2);
							break;
						}
					case SDLK_3:
						if (clicked_cust == true){
							clicked_cust = false;
							cust -> clicked(3);
							break;
						}
					case SDLK_4:
						if (clicked_cust == true){
							clicked_cust = false;
							cust -> clicked(4);
							break;
						}
					default:
						break;
					
				} 
			}

			if(e.type == SDL_MOUSEBUTTONDOWN){ //mouse input
				int xMouse, yMouse;
				SDL_GetMouseState(&xMouse,&yMouse);
				if (xMouse >= 150 & xMouse <= 250 & yMouse >= 200 & yMouse <= 400){ //clicked on customer
					clicked_cust = true;
				}

				else if (xMouse >= 40 & xMouse <= 100 & yMouse >= 515 & yMouse <= 540 & w.get_move_x () <= 390 & w.get_move_y() >= 400  &  picked_f==false ){
					picked = obj.clicked_on(0, w); //picked food from first location of counter
					picked_f = true;
					counter_number = 0;
				}
				else if (xMouse >= 140 & xMouse <= 200 & yMouse >= 515 & yMouse <= 540 & w.get_move_x () <= 390 & w.get_move_y() >= 400 & picked_f==false){
					picked = obj.clicked_on(1, w); //picked food from second location of counter
					picked_f = true;
					counter_number = 1;
				}
				else if (xMouse >= 240 & xMouse <= 300 & yMouse >= 515 & yMouse <= 540 & w.get_move_x () <= 390 & w.get_move_y() >= 400 & picked_f==false){
					picked = obj.clicked_on(2, w); //picked food from third location of counter
					picked_f = true;
					counter_number = 2;
				}
				else if (xMouse >= 340 & xMouse <= 400 & yMouse >= 515 & yMouse <= 540 & w.get_move_x () <= 390 & w.get_move_y() >= 400 & picked_f==false){
					picked = obj.clicked_on(3, w); //picked food from fourth location of counter
					picked_f = true;
					counter_number = 3;
				}

				else if (xMouse >= 240 & xMouse <= 280 & yMouse >= 150 & yMouse <= 180 & w.get_move_x () <= 369 & w.get_move_x() >= 149 & w.get_move_y () <= 267 & w.get_move_y() >= 111 & picked_f == true){
					if (cust -> comparefood(picked, 1) == true){ //delivering food, checks if the food is the same as the one ordered
						picked -> set_mover(260, 150,35,35);
						picked -> delivered = true;
						picked_f = false;
					}
				}
				else if (xMouse >= 390 & xMouse <= 440 & yMouse >= 340 & yMouse <= 370 & w.get_move_x () <= 522 & w.get_move_x() >= 274 & w.get_move_y () >= 302 & w.get_move_y() <= 462 & picked_f == true){
					if (cust -> comparefood(picked, 3) == true){ //delivering food, checks if the food is the same as the one ordered
						picked -> set_mover(410, 340,35,35);
						picked -> delivered = true;
						picked_f = false;
					}
				}
				else if (xMouse >= 600 & xMouse <= 700 & yMouse >= 160 & yMouse <= 190 & w.get_move_x () <= 750 & w.get_move_x() >= 530 & w.get_move_y () >= 129 & w.get_move_y() <= 272 & picked_f == true){
					if (cust -> comparefood(picked, 2) == true){ //delivering food, checks if the food is the same as the one ordered
						picked -> set_mover(650, 160,35,35);
						picked -> delivered = true;
						picked_f = false;
					}
				}
				else if (xMouse >= 740 & xMouse <= 850 & yMouse >= 350 & yMouse <= 400 & w.get_move_x () <= 926 & w.get_move_x() >= 679 & w.get_move_y () >= 308 & w.get_move_y() <= 479 & picked_f == true){
					if (cust -> comparefood(picked, 4) == true){ //delivering food, checks if the food is the same as the one ordered
						picked -> set_mover(790, 350,35,35);
						picked -> delivered = true;
						picked_f = false;
					}
				}

				else if (xMouse >= 170 & xMouse <= 270 & yMouse >= 120 & yMouse <= 220 & w.get_move_x () <= 369 & w.get_move_x() >= 149 & w.get_move_y () <= 267 & w.get_move_y() >= 111 & picked_f == false){
					cust -> money_pickup(1);
				}
				else if (xMouse >= 320 & xMouse <= 420 & yMouse >= 320 & yMouse <= 420 & w.get_move_x () <= 522 & w.get_move_x() >= 274 & w.get_move_y () >= 302 & w.get_move_y() <= 462 & picked_f == false){
					cust -> money_pickup(3);
				}
				else if (xMouse >= 560 & xMouse <= 660 & yMouse >= 140 & yMouse <= 240 & w.get_move_x () <= 750 & w.get_move_x() >= 530 & w.get_move_y () >= 129 & w.get_move_y() <= 272 & picked_f == false){
					cust -> money_pickup(2);
				}
				else if (xMouse >= 670 & xMouse <= 770 & yMouse >= 320 & yMouse <= 420 & w.get_move_x () <= 926 & w.get_move_x() >= 679 & w.get_move_y () >= 308 & w.get_move_y() <= 479 & picked_f == false){
					cust -> money_pickup(4);
				}
			}
		}
		
		SDL_RenderClear(gRenderer); //removes everything from renderer
		SDL_RenderCopy(gRenderer, temp_bg, NULL, NULL);//Draws background to renderer

		if (cust->lose() == true){
			l_b = true; //trigger for lose screen
			play = false;
		}

		if (cust->win() == true){
			w_b = true; //trigger for win screen
			play = false;
		}

		if (play == true){
			SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
			w.draw(gRenderer, waiter, bean_sit, heart, orderbubble, food_img, money);
			cust -> draw(gRenderer, customers, bean_sit, heart, orderbubble, food_img, money);
			if (picked_f == true){ //if the food is picked, the counter is made empty and the move function is called
				if (delete_food == true){
					obj.delete_food();
					delete_food = false;
					counter_number = 5;
					picked_f = false;
				}
				else{
					picked -> counter_number = 5;
					picked -> move(w); //food moves with waiter
				}
			}
		}

		else if (instructions == true & play == false ){
			SDL_RenderCopy(gRenderer, temp_ins, NULL, NULL); //draws instruction screen
		}
		else if(w_b == true){
			SDL_RenderCopy(gRenderer, win, NULL, NULL); //draws win screen
		}
		else if(l_b == true){
			SDL_RenderCopy(gRenderer, lose, NULL, NULL); //draws lose screen
		}
		
    	SDL_RenderPresent(gRenderer); //displays the updated renderer
		
	    SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds
	}
	cust->~customer_class();
	obj.~ObjectCreator();

}
	
