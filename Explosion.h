#ifndef Explosion_H_
#define Explosion_H_


#include "BaseObject.h"
#include "CommonFunction.h"

const int EXPLOSION_WIDTH = 150 ;
const int EXPLOSION_HEIGHT = 165 ;


class explosion_object : public base_object
{
public:
    explosion_object();
    ~explosion_object();
    void set_clip ();
    void set_frame ( const int  fr ) { frame_ = fr ; }
    virtual bool LoadImg_ ( string path , SDL_Renderer* screen ) ;
    void Show_ (SDL_Renderer* screen ) ;
public:
    int frame_;
    SDL_Rect frame_clip_[8];
};




#endif // Explosion_H_
