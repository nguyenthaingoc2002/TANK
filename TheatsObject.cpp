#include "TheatsObject.h"

TheatsObject :: TheatsObject (int x_ , int y_ , DIRECTION direction_tank_ , int x_val_ , int y_val_ , int number_tank_ )
{
    number_tank = number_tank_;
    rect_.x = x_;
    rect_.y = y_;
    direction_tank = direction_tank_ ;
    x_val = x_val_ ;
    y_val = y_val_ ;
    timeDie = 0 ;
}

TheatsObject :: ~TheatsObject ()
{

}

void TheatsObject :: XuLy ( SDL_Renderer* screen , int Map[20][20] )
{
    bool can_direction[10] ;
    for ( int i = 1 ; i <= 4 ; i++ )
    {
        can_direction[i] = true;
    }
    can_direction[direction_tank] = false;
    if ( going == false )
    {
        rect_.x = rect_.x - x_val ;
        rect_.y = rect_.y - y_val;
    }
    while ( going == false && is_living == true && can_direction[direction_tank] == false  )
    {
        int random = 1 + rand() % ( 4  );
        switch ( random )
        {
        case 1 :
            {
                x_val = x_val - STEP_H;
                direction_tank = LEFT ;
                going = true;
                break;
            }
        case 2 :
            {
                x_val = x_val + STEP_H;
                direction_tank = RIGHT ;
                going = true;
                break;
            }
        case 3 :
            {
                y_val = y_val - STEP_H;
                direction_tank = UP ;
                going = true;
                break;
            }
        case 4 :
            {
                y_val = y_val + STEP_H;
                direction_tank = DOWN ;
                going = true;
                break;
            }
        }
        if( rect_.x + x_val < PlayWindow_X  || (rect_.x + MAIN_SIZE + x_val ) > (PlayWindow_X+PlayWindow_SIZE) )
        {
            going =  false ;
            x_val = 0 ;
            y_val = 0 ;
            can_direction[direction_tank] = false;
        }
        if(rect_.y + y_val < PlayWindow_Y || (rect_.y + MAIN_SIZE + y_val ) > ( PlayWindow_Y + PlayWindow_SIZE ) )
        {
            going =  false ;
            x_val = 0 ;
            y_val = 0 ;
            can_direction[direction_tank] = false;
        }
        int x1 = ( rect_.x + x_val - PlayWindow_X  ) / MAIN_SIZE ;
        int x2 = ( rect_.x + x_val + MAIN_SIZE  - PlayWindow_X - 1  ) / MAIN_SIZE ;
        int y1 = ( rect_.y + y_val - PlayWindow_Y  ) / MAIN_SIZE ;
        int y2 = ( rect_.y + y_val + MAIN_SIZE  - PlayWindow_Y - 1  ) / MAIN_SIZE ;


        if ( Map[y1][x1] != number_tank || Map[y1][x2] != number_tank || Map[y2][x1] != number_tank || Map[y2][x2] != number_tank )
        {
            going =  false ;
            x_val = 0 ;
            y_val = 0 ;
            can_direction[direction_tank] = false;
        }
    }
    if( rect_.x + x_val < PlayWindow_X  || (rect_.x + MAIN_SIZE + x_val ) > (PlayWindow_X+PlayWindow_SIZE) )
    {
        going =  false ;
        x_val = 0 ;
        y_val = 0 ;
    }
    if(rect_.y + y_val < PlayWindow_Y || (rect_.y + MAIN_SIZE + y_val ) > ( PlayWindow_Y + PlayWindow_SIZE ) )
    {
        going =  false ;
        x_val = 0 ;
        y_val = 0 ;
    }
    int x1 = ( rect_.x + x_val - PlayWindow_X  ) / MAIN_SIZE ;
    int x2 = ( rect_.x + x_val + MAIN_SIZE  - PlayWindow_X - 1  ) / MAIN_SIZE ;
    int y1 = ( rect_.y + y_val - PlayWindow_Y  ) / MAIN_SIZE ;
    int y2 = ( rect_.y + y_val + MAIN_SIZE  - PlayWindow_Y - 1  ) / MAIN_SIZE ;


    if ( Map[y1][x1] != number_tank || Map[y1][x2] != number_tank || Map[y2][x1] != number_tank || Map[y2][x2] != number_tank )
    {
        going =  false ;
        x_val = 0 ;
        y_val = 0 ;
    }
    if ( going == true )
    {
        rect_.x += x_val;
        rect_.y += y_val;
    }
    unsigned currentTime = SDL_GetTicks();
    if ( currentTime - bullet_time > 1500 && is_living == true )
    {
        bullet_time = currentTime ;
        bullet_object* p_bullet = new bullet_object();
        switch ( direction_tank )
        {
            case LEFT :
            {
                p_bullet->SetRect(rect_.x , rect_.y + MAIN_SIZE/2 - 5 ) ;
                p_bullet->set_x_val(-SPEED_BULLET);
                break;
            }
            case RIGHT :
            {
                p_bullet->SetRect(rect_.x + MAIN_SIZE , rect_.y + MAIN_SIZE/2 - 5 ) ;
                p_bullet->set_x_val(SPEED_BULLET);
                break;
            }
            case UP :
            {
                p_bullet->SetRect(rect_.x + MAIN_SIZE/2 - 5 , rect_.y  );
                p_bullet->set_y_val(-SPEED_BULLET);
                break;
            }
            case DOWN :
            {
                p_bullet->SetRect(rect_.x + MAIN_SIZE/2 - 5 , rect_.y + MAIN_SIZE );
                p_bullet->set_y_val(SPEED_BULLET);
                break;
            }
        }
        p_bullet->LoadImg("img//bullet_enemy.png" , screen , BULLET_SIZE , BULLET_SIZE ) ;
        p_bullet->set_is_move(true);
        p_bullet_list_.push_back(p_bullet);

    }

}

/*void TheatsObject :: XuLy ( SDL_Renderer* screen , int Map[20][20] )
{
    while ( going == false && is_living == true  )
    {
    int random = 1 + rand() % ( 4 + 1 - 1 );
    switch ( random )
    {
        case 1 :
        {
            y_val = y_val - STEP_H ;
            direction_tank = UP ;
            if ( Check (x_val , y_val) == true && direction_tank != now  )
            {
                going = true ;
            }
            else
            {
                x_val = 0 ;
                y_val = 0 ;
            }
            break;
        }
        case 2 :
        {
            x_val = x_val + STEP_H;
            direction_tank = RIGHT ;
            if ( Check (x_val , y_val) == true && direction_tank != now  )
            {
                going = true ;
            }
            else
            {
                x_val = 0 ;
                y_val = 0 ;
            }
            break;
        }
        case 3 :
        {
            y_val = y_val + STEP_H;
            direction_tank = DOWN ;
            if ( Check (x_val , y_val) == true   && direction_tank != now )
            {
                going = true ;
            }
            else
            {
                x_val = 0 ;
                y_val = 0 ;
            }
            break;
        }
        case 4 :
        {
            x_val = x_val - STEP_H;
            direction_tank = LEFT ;
            if ( Check (x_val , y_val) == true && direction_tank != now  )
            {
                going = true ;
            }
            else
            {
                x_val = 0 ;
                y_val = 0 ;
            }
            break;
        }

    }

    }

    if( rect_.x + x_val < PlayWindow_X  || (rect_.x + MAIN_SIZE + x_val ) > (PlayWindow_X+PlayWindow_SIZE) )
    {
        going =  false ;
        x_val = 0 ;
        y_val = 0 ;

    }
    if(rect_.y + y_val < PlayWindow_Y || (rect_.y + MAIN_SIZE + y_val ) > ( PlayWindow_Y + PlayWindow_SIZE ) )
    {
        going =  false ;
        x_val = 0 ;
        y_val = 0 ;

    }
    int x1 = ( rect_.x + x_val - PlayWindow_X  ) / MAIN_SIZE ;
    int x2 = ( rect_.x + x_val + MAIN_SIZE  - PlayWindow_X - 1  ) / MAIN_SIZE ;
    int y1 = ( rect_.y + y_val - PlayWindow_Y  ) / MAIN_SIZE ;
    int y2 = ( rect_.y + y_val + MAIN_SIZE  - PlayWindow_Y - 1  ) / MAIN_SIZE ;


    if ( Map[y1][x1] == 1 || Map[y1][x2] == 1 || Map[y2][x1] == 1 || Map[y2][x2] == 1 )
    {
        going =  false ;
        x_val = 0 ;
        y_val = 0 ;
    }


    if ( going == true )
    {
        rect_.x = rect_.x + x_val ;
        rect_.y = rect_.y + y_val;
    }




    unsigned currentTime = SDL_GetTicks();
    if ( currentTime - bullet_time > 2000 && is_living == true )
    {
        bullet_time = currentTime ;
        bullet_object* p_bullet = new bullet_object();
        switch ( direction_tank )
        {
            case LEFT :
            {
                p_bullet->SetRect(rect_.x , rect_.y + MAIN_SIZE/2 - 5 ) ;
                p_bullet->set_x_val(-SPEED_BULLET);
                break;
            }
            case RIGHT :
            {
                p_bullet->SetRect(rect_.x + MAIN_SIZE , rect_.y + MAIN_SIZE/2 - 5 ) ;
                p_bullet->set_x_val(SPEED_BULLET);
                break;
            }
            case UP :
            {
                p_bullet->SetRect(rect_.x + MAIN_SIZE/2 - 5 , rect_.y  );
                p_bullet->set_y_val(-SPEED_BULLET);
                break;
            }
            case DOWN :
            {
                p_bullet->SetRect(rect_.x + MAIN_SIZE/2 - 5 , rect_.y + MAIN_SIZE );
                p_bullet->set_y_val(SPEED_BULLET);
                break;
            }
        }
        p_bullet->LoadImg("img//bullet_enemy.png" , screen , BULLET_SIZE , BULLET_SIZE ) ;
        p_bullet->set_is_move(true);
        p_bullet_list_.push_back(p_bullet);

    }

}*/

bool TheatsObject :: Check ( int x , int y )
{
    if( rect_.x + x < PlayWindow_X  || (rect_.x + MAIN_SIZE + x ) > (PlayWindow_X+PlayWindow_SIZE) )
    {
        return false ;
    }
    if(rect_.y + y < PlayWindow_Y || (rect_.y + MAIN_SIZE + y ) > ( PlayWindow_Y + PlayWindow_SIZE ) )
    {
        return false ;
    }
    /*int x1 = ( rect_.x + x - 350 ) / MAIN_SIZE ;
    int x2 = ( rect_.x + x + MAIN_SIZE - 2 - 350 ) / MAIN_SIZE ;
    int y1 = ( rect_.y + y - 50 ) / MAIN_SIZE ;
    int y2 = ( rect_.y + y + MAIN_SIZE - 2 - 50  ) / MAIN_SIZE ;

    if ( Map[y1][x1] == 1 || Map[y1][x2] == 1 || Map[y2][x1] == 1 || Map[y2][x2] == 1 )
    {
        return false ;
    }*/

    return true ;

}


void TheatsObject :: HandleMove(  )
{
    /*// xu ly cho tank nam trong man hinh choi game
    if( rect_.x + x_val < PlayWindow_X  || (rect_.x + x_val + MAIN_SIZE) > (PlayWindow_X+PlayWindow_SIZE) )
    {
        //rect_.x = rect_.x - x_val;
        x_val = 0 ;
        y_val = 0 ;
        going = false ;
    }
    if(rect_.y + y_val < PlayWindow_Y || (rect_.y + MAIN_SIZE + y_val ) > ( PlayWindow_Y + PlayWindow_SIZE ) )
    {
        //rect_.y = rect_.y -  y_val;
        x_val = 0 ;
        y_val = 0 ;
        going = false ;
    }

    // xu ly cho tank khong duoc di xuyen tuong
    int x1 = ( rect_.x + x_val - 350 ) / MAIN_SIZE ;
    int x2 = ( rect_.x + x_val + MAIN_SIZE - 2 - 350 ) / MAIN_SIZE ;
    int y1 = ( rect_.y + y_val - 50 ) / MAIN_SIZE ;
    int y2 = ( rect_.y + y_val + MAIN_SIZE - 2 - 50  ) / MAIN_SIZE ;

    if ( Map[y1][x1] == 1 || Map[y1][x2] == 1 || Map[y2][x1] == 1 || Map[y2][x2] == 1 )
    {
        //rect_.x = rect_.x - x_val ;
        //rect_.y = rect_.y - y_val;
        going = false ;
        x_val = 0 ;
        y_val = 0 ;
    }*/
    /*if ( going == true )
    {
        rect_.x = rect_.x + x_val ;
        rect_.y = rect_.y + y_val;
    }*/
        rect_.x = rect_.x + x_val ;
        rect_.y = rect_.y + y_val;
}


//bool kiemtra ( )





void TheatsObject :: Show(SDL_Renderer* screen)
{

        switch ( direction_tank )
        {
        case LEFT :
        {
            LoadImg("img//tank_enemy_left.png", screen , MAIN_SIZE  , MAIN_SIZE );
            break;
        }
        case RIGHT :
        {
            LoadImg("img//tank_enemy_right.png", screen , MAIN_SIZE  , MAIN_SIZE );
            break;
        }
        case UP :
        {
            LoadImg("img//tank_enemy_up.png", screen , MAIN_SIZE  , MAIN_SIZE  );
            break;
        }
        case DOWN :
        {
            LoadImg("img//tank_enemy_down.png", screen , MAIN_SIZE , MAIN_SIZE );
            break;
        }

        }


        if ( is_living == true )
        {
            Render(screen);
        }

}




void TheatsObject :: MakeBullet ( SDL_Renderer* screen , int MapMap[20][20] )
{
    for ( int i = 0 ; i < p_bullet_list_.size() ; i++ )
    {
        bullet_object* p_bullet = p_bullet_list_.at(i) ;
        if ( p_bullet != NULL )
        {
            if ( p_bullet->get_is_move() )
            {
                p_bullet->Render(screen);
                p_bullet->handle_move(MapMap);
            }
            else
            {
                if ( p_bullet != NULL )
                {
                    p_bullet_list_.erase( p_bullet_list_.begin() + i ) ;
                    delete p_bullet ;
                    p_bullet = NULL ;
                }
            }
        }
    }
}


void TheatsObject :: RemoveBullet ( const int& idx )
{
    int size = p_bullet_list_.size();
    if ( size > 0 && idx < size )
    {
        bullet_object* p_bullet = p_bullet_list_.at(idx);
        p_bullet_list_.erase ( p_bullet_list_.begin() + idx );
        if ( p_bullet != NULL )
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}
