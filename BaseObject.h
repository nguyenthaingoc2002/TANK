#ifndef BaseObject_H_
#define BaseObject_H_

#include"CommonFunction.h"

class base_object
{
public:
    base_object();
    ~base_object();
    void SetRect( const int x , const int y ) { rect_.x = x , rect_.y = y ;}
    SDL_Rect GetRect()  { return rect_ ; }
    void SetRect_ ( SDL_Rect rect__ ) { rect_ = rect__ ;}
    SDL_Texture* GetObject() const  { return p_object_ ; }
    bool LoadImg ( string path , SDL_Renderer* screen , int w_ , int h_ );
    void Render ( SDL_Renderer* des  );
    void Free();
protected:
    SDL_Texture* p_object_ ;
    SDL_Rect rect_;

};


#endif // BaseObject_H_

