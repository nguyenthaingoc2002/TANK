#include "Explosion.h"


explosion_object :: explosion_object()
{
    frame_ = 100 ;
}

explosion_object :: ~explosion_object()
{

}

bool explosion_object :: LoadImg_ ( string path , SDL_Renderer* screen )
{
    bool ret = base_object :: LoadImg(path , screen , MAIN_SIZE , MAIN_SIZE ) ;
    return ret;
}

void explosion_object :: set_clip ()
{

        for ( int i = 0 ; i < 8  ; i++ )
        {
            frame_clip_[i].x = EXPLOSION_WIDTH*i;
            frame_clip_[i].y = 0 ;
            frame_clip_[i].w = EXPLOSION_WIDTH ;
            frame_clip_[i].h = EXPLOSION_HEIGHT;
        }

}

void explosion_object :: Show_(SDL_Renderer* screen )
{
    if ( frame_ < 8 )
    {
    SDL_Rect current_clip = frame_clip_[frame_];
    SDL_Rect render_quad = {rect_.x , rect_.y , rect_.h , rect_ . w };
    SDL_RenderCopy( screen , p_object_ , &current_clip , &render_quad );
    frame_++;
    }
}
