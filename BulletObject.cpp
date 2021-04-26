#include "BulletObject.h"


bullet_object :: bullet_object ()
{
    x_val_ = 0 ;
    y_val_ = 0 ;
    is_move_ = false;
}

bullet_object :: ~bullet_object ()
{

}


void bullet_object :: handle_move ( int MapMap[20][20] )
{
    rect_.x = rect_.x + x_val_ ;
    rect_.y = rect_.y + y_val_ ;

    // lam cho vien dan khong bay ra khoi ban do
    if( rect_.x  < PlayWindow_X  || (rect_.x  + BULLET_SIZE ) > (PlayWindow_X+PlayWindow_SIZE) )
    {
        is_move_ = false ;
    }
    if(rect_.y  < PlayWindow_Y || (rect_.y + BULLET_SIZE  ) > ( PlayWindow_Y + PlayWindow_SIZE ) )
    {
        is_move_ = false ;
    }

    // lam cho vien dan khong bay xuyen tuong

    int x1 = ( rect_.x + x_val_ - PlayWindow_X  ) / MAIN_SIZE ;
    int x2 = ( rect_.x + x_val_ + BULLET_SIZE  - PlayWindow_X - 1  ) / MAIN_SIZE ;
    int y1 = ( rect_.y + y_val_ - PlayWindow_Y  ) / MAIN_SIZE ;
    int y2 = ( rect_.y + y_val_ + BULLET_SIZE  - PlayWindow_Y - 1  ) / MAIN_SIZE ;

    if ( MapMap[y1][x1] == 1 || MapMap[y1][x2] == 1 || MapMap[y2][x1] == 1 || MapMap[y2][x2] == 1 )
    {
        is_move_ = false ;
    }

}

