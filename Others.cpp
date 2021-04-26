#include "Others.h"


void back_end :: LoadImg (SDL_Renderer* screen , TTF_Font* gFont , SDL_Color textColor )
{
    picture_live.LoadImg( "img//tank_up.png" , screen , MAIN_SIZE* 3 , MAIN_SIZE * 3 );
    picture_live.SetRect(130 + MAIN_SIZE* 3 , 100);

    score_text.loadFromRenderedText( "SCORE" , gFont , textColor , screen , 120 , 100 );

    number_bullet_text.loadFromRenderedText("NUMBER BULLET" , gFont , textColor , screen , 350 , 100 );

    picture_oclock.LoadImg("img//oclock.png" , screen , 150 , 150 );
    picture_oclock.SetRect( 1080 , 400 );
}


void back_end :: LIVE ( string live, TTF_Font* gFont , SDL_Color textColor , SDL_Renderer* screen   )
{
    TextObject live_;
    live_.loadFromRenderedText( live + "x" , gFont , textColor , screen , 120 , 100 );
    live_.render(screen , 90 , 100 );
    picture_live.Render(screen);
}

void back_end :: SCORE ( string score, TTF_Font* gFont , SDL_Color textColor , SDL_Renderer* screen   )
{
    TextObject score_;
    score_.loadFromRenderedText(score , gFont , textColor , screen , 120 , 100 );
    score_text.render(screen , 1100 , 100 );
    score_.render(screen , 1100 , 200 );
}

void back_end :: NUMBER_BULLET ( string number_bullet , TTF_Font* gFont , SDL_Color textColor , SDL_Renderer* screen   )
{
    TextObject number_bullet_;

    number_bullet_.loadFromRenderedText(number_bullet , gFont , textColor , screen , 200 , 100 );
    number_bullet_text.render(screen , 30  , 400 );
    number_bullet_.render(screen , 110  , 500 );

}


void back_end :: TIME ( int time_game , TTF_Font* gFont , SDL_Color textColor , SDL_Renderer* screen  )
{
    int second = time_game / 1000 ;
    int minutes = second / 60 ;
    second = second % 60 ;

    string second_;
    string minutes_;
    if ( second < 10 )  second_ = "0" + to_string (second);
    else  second_ = to_string (second);
    if ( minutes < 10 )  minutes_ = "0" + to_string (minutes);
    else  minutes_ = to_string (minutes);
    string res = minutes_  + " : " + second_ ;

    TextObject oclock;
    oclock.loadFromRenderedText(res , gFont , textColor , screen , 170 , 130 );
    oclock.render ( screen , 1080 , 550 );

    picture_oclock.Render(screen);
}
