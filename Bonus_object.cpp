#include"Bonus_object.h"


gift::gift()
{

}

gift::~gift()
{

}


void gift :: LoadImg_(SDL_Renderer* screen )
{
    switch (type_gift)
    {
    case 1:
        {
            LoadImg("img//bonus_tank.png" , screen , MAIN_SIZE , MAIN_SIZE );
            break;
        }
    case 2:
        {
            LoadImg("img//bonus_gun.png" , screen , MAIN_SIZE , MAIN_SIZE );
            break;
        }
    case 3:
        {
            LoadImg("img//bonus_helmet.png" , screen , MAIN_SIZE , MAIN_SIZE );
            break;
        }
    }
}

void gift :: Show (SDL_Renderer* screen )
{
    if ( is_living == true )
    {
        Render(screen);
    }
}

void gift::gogo ( int MapMap[20][20] )
{

    if (is_living == false /*&& SDL_GetTicks() - timeDie > 10000*/ )
    {
        int random , random1 , random2;
        random = 1 + rand() % ( 3  );
        type_gift = random;
        cout << random << endl;
    do
    {
        random1 = 0 + rand() % ( 19  );
        random2 = 0 + rand() % ( 19  );
    }while ( MapMap[random2][random1] == 1 );

    SetRect( PlayWindow_X + random1*MAIN_SIZE , PlayWindow_Y + random2*MAIN_SIZE);
    is_living = true;
    }
}






