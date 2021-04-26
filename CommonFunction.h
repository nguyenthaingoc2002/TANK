#ifndef CommonFunction_H_
#define CommonFunction_H_

#include <time.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdlib.h>

using namespace std ;




const int SCREEN_WIDTH = 1366 ;
const int SCREEN_HEIGHT = 768 ;
const int SCREEN_BBP = 32 ;

const int COLOR_KEY_R = 122;
const int COLOR_KEY_G = 122;
const int COLOR_KEY_B = 122;
const int RENDER_DRAW_COLOR = 0 ;
const int STEP = 5 ;
const int STEP_H = 1 ;
const int MAIN_SIZE = 30 ;
const int PlayWindow_SIZE = 600;
const int PlayWindow_Y = ( SCREEN_HEIGHT - PlayWindow_SIZE ) / 2 ; //84
const int PlayWindow_X = ( SCREEN_WIDTH  - PlayWindow_SIZE ) / 2 ; //383
const int SPEED_BULLET = 5 ;
const int BULLET_SIZE = 5 ;
const int FPS = 60 ;
const int NUM_FRAME_EXPLOSION = 8 ;
//const int MAX_NUMBER_BULLET_MAIN = 1 ;

enum DIRECTION
{
    LEFT = 1,
    RIGHT = 2 ,
    UP = 3 ,
    DOWN = 4
};

bool checkCollision  ( const SDL_Rect a , const SDL_Rect b );



#define TILE_SIZE 64
#define MAX_MAP 20




#endif // CommonFunction_H_

