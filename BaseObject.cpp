
#include "BaseObject.h"



base_object :: base_object()
{
    p_object_ = NULL ;
    rect_.x = 0 ;
    rect_.y = 0 ;
    rect_.w = 0 ;
    rect_.h = 0 ;
}


base_object :: ~base_object()
{
    Free();
}

bool base_object :: LoadImg ( string path , SDL_Renderer* screen , int w_ , int h_ )
{

    SDL_Texture* new_texture = NULL ;
    SDL_Surface* load_surface = IMG_Load ( path.c_str() );
    if ( load_surface != NULL )
    {
        SDL_SetColorKey ( load_surface , SDL_TRUE , SDL_MapRGB ( load_surface->format , COLOR_KEY_R , COLOR_KEY_G , COLOR_KEY_B )) ;
        new_texture = SDL_CreateTextureFromSurface(screen , load_surface );
        if ( new_texture != NULL )
        {
            /*rect_.w = load_surface->w ;
            rect_.h = load_surface->h ;*/
            rect_.w = w_ ;
            rect_.h = h_ ;
        }

        SDL_FreeSurface(load_surface);
    }

    SDL_DestroyTexture(p_object_);
    p_object_ = new_texture;
    return (p_object_ != NULL );

}


void base_object :: Render ( SDL_Renderer* des   /*= NULL*/ )
{
    SDL_Rect renderquad = { rect_.x , rect_.y , rect_.w , rect_.h };
    SDL_RenderCopy (des , p_object_ , NULL , &renderquad );

}

void base_object :: Free()
{
    if (p_object_ != NULL )
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL ;
        rect_.w = 0 ;
        rect_.h = 0 ;
    }
}
