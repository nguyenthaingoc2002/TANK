#include "GameMap.h"




void TileMap :: Load_Map ( string name )
{
    std::ifstream ifs;
    ifs.open(name,std::ios::in);

    for ( int i = 0 ; i < MAX_MAP ; i++ )
    {
        for ( int j = 0 ; j < MAX_MAP ; j++ )
        {
            ifs >>  MapMap[i][j] ;
        }
    }

}


void TileMap :: Draw_Map ( SDL_Renderer* screen )
{
    wall.LoadImg("img//wall.png" , screen , MAIN_SIZE , MAIN_SIZE );
    int x = ( SCREEN_WIDTH  - 600 ) / 2 ;
    int y = ( SCREEN_HEIGHT - 600 ) / 2 ;
    for ( int i = 0 ; i < MAX_MAP ; i++ )
    {
        for ( int j = 0 ; j < MAX_MAP ; j++ )
        {
            if ( MapMap[i][j] == 1 )
            {
                wall.SetRect(x,y);
                wall.Render(screen);
            }
            x = x + 30 ;
        }
        x = ( SCREEN_WIDTH  - 600 ) / 2 ;
        y = y + 30 ;
    }

}







