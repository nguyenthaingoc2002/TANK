#include"TextObject.h"


TextObject :: TextObject()
{
    mTexture = NULL ;
    mHeight = 0 ;
    mWidth = 0 ;
}

TextObject :: ~TextObject()
{
    free();
}

bool TextObject::loadFromFile( string path , SDL_Renderer* screen , int w_ , int h_  )
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		return false ;
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( screen, loadedSurface );
		if( newTexture == NULL )
		{
		    return false ;
		}
		else
		{
			mWidth = w_;
			mHeight = h_;
		}

		SDL_FreeSurface( loadedSurface );
	}
	mTexture = newTexture;
	return mTexture != NULL;
}


bool TextObject::loadFromRenderedText( string textureText, TTF_Font* gFont , SDL_Color textColor , SDL_Renderer* screen , int w_ , int h_  )
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		return false ;
	}
	else
	{
        mTexture = SDL_CreateTextureFromSurface( screen , textSurface );
		if( mTexture == NULL )
		{
			return false ;
		}
		else
		{
			mWidth = w_;
			mHeight = h_;
		}

		SDL_FreeSurface( textSurface );
	}

	return mTexture != NULL;
}

void TextObject::free()
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void TextObject::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void TextObject::setBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( mTexture, blending );
}

void TextObject::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void TextObject::render( SDL_Renderer* screen , int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };



	SDL_RenderCopyEx ( screen , mTexture, clip, &renderQuad, angle, center, flip ) ;
}

int TextObject::getWidth()
{
	return mWidth;
}

int TextObject::getHeight()
{
	return mHeight;
}
