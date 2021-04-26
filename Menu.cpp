#include"Menu.h"

Menu :: Menu()
{
    //menu_.p_object_ = NULL ;
    //menu_.rect_ = NULL ;
}
Menu :: ~Menu()
{

}

void Menu :: XuLy ( SDL_Event event , SDL_Renderer* screen , bool &is_quit  )
{
    menu_.LoadImg("img//menu1.png" , screen , SCREEN_WIDTH , SCREEN_HEIGHT );
    bool quit = false;
    int k = 1 ;
    while( !quit )
    {
        while ( SDL_PollEvent(&event) )
        {

            if ( event.type == SDL_KEYDOWN  )
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_DOWN :
                    {
                        menu_.LoadImg("img//menu2.png" , screen , SCREEN_WIDTH , SCREEN_HEIGHT );
                        k = 2 ;
                        break;
                    }
                    case SDLK_UP :
                    {
                        menu_.LoadImg("img//menu1.png" , screen , SCREEN_WIDTH , SCREEN_HEIGHT );
                        k = 1 ;
                        break;
                    }
                    case SDLK_RETURN:
                    {
                        quit = true ;
                        if ( k == 1 )
                        {
                            is_quit = false ;
                        }
                        if ( k == 2 )
                        {
                            is_quit = true ;
                        }
                        break;
                    }
                    default: break;

                }
            }
        }


        menu_.Render( screen );
        SDL_RenderPresent(screen);
    }
}
