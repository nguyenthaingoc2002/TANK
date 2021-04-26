#ifndef TextObject_H_
#define TextObject_H_


#include "CommonFunction.h"

class TextObject
{
public:
    TextObject();
    ~TextObject();
    bool loadFromFile( string path , SDL_Renderer* screen , int w_ , int h_ );
    bool loadFromRenderedText( string textureText,  TTF_Font* gFont , SDL_Color textColor , SDL_Renderer* screen , int w_ , int h_ );
    void free();
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );
    void render( SDL_Renderer* screen , int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};



#endif // TextObject_H_
