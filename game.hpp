#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <SDL_mixer.h>

class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = 1027;
    const int SCREEN_HEIGHT = 579;
    
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    Mix_Music *gMusic = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    SDL_Texture* temp_bg = NULL;
    SDL_Texture* temp_ins = NULL;
    SDL_Texture* lose = NULL;
    SDL_Texture* win = NULL;

    //global reference to png image sheets
    SDL_Texture* waiter=NULL;
    SDL_Texture* money=NULL;
    SDL_Texture* food_img=NULL;
    SDL_Texture* customers=NULL;
    SDL_Texture* orderbubble=NULL;
    SDL_Texture* bean_sit=NULL;
    SDL_Texture* heart=NULL;


public:
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    void run();
};

