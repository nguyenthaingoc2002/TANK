#include "MainObject.h"



main_object :: main_object()
{
    rect_.x = PlayWindow_X + 300  ;
    rect_.y = PlayWindow_Y + PlayWindow_SIZE - MAIN_SIZE - 300 ;
    direction_tank = UP ;
    x_val = 0 ;
    y_val = 0 ;
    timeDie = 0 ;
}


main_object :: ~main_object()
{

}



void main_object::HandleInputAction( SDL_Event event , SDL_Renderer* screen , Mix_Chunk* fire )
{
    if ( event.type == SDL_KEYDOWN && is_living == true  )
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_LEFT :
            {
                x_val = x_val - STEP;
                direction_tank = LEFT ;
                break;
            }
            case SDLK_RIGHT :
            {
                x_val = x_val + STEP;
                direction_tank = RIGHT ;
                break;
            }
            case SDLK_UP :
            {
                y_val = y_val - STEP;
                direction_tank = UP ;
                break;
            }
            case SDLK_DOWN :
            {
                y_val = y_val + STEP;
                direction_tank = DOWN ;
                break;
            }
            case SDLK_SPACE :
            {
                if ( p_bullet_list_.size() < MAX_NUMBER_BULLET_MAIN )
                {
                Mix_PlayChannel(-1,fire,0);
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
                p_bullet->LoadImg("img//bullet.png",screen , BULLET_SIZE , BULLET_SIZE ) ;
                p_bullet->set_is_move(true);
                p_bullet_list_.push_back(p_bullet);

                }

            }
            default : break;
        }

    }
}




void main_object :: HandleMove( int Map [20][20] )
{
    // xu ly cho tank nam trong man hinh choi game
    if( rect_.x + x_val < PlayWindow_X  || (rect_.x + x_val + MAIN_SIZE) > (PlayWindow_X+PlayWindow_SIZE) )
    {
        rect_.x = rect_.x - x_val;
    }
    if(rect_.y + y_val < PlayWindow_Y || (rect_.y + MAIN_SIZE + y_val ) > ( PlayWindow_Y + PlayWindow_SIZE ) )
    {
        rect_.y = rect_.y -  y_val;
    }

    // xu ly cho tank khong duoc di xuyen tuong
    int x1 = ( rect_.x + x_val - PlayWindow_X  ) / MAIN_SIZE ;
    int x2 = ( rect_.x + x_val + MAIN_SIZE  - PlayWindow_X - 1  ) / MAIN_SIZE ;
    int y1 = ( rect_.y + y_val - PlayWindow_Y  ) / MAIN_SIZE ;
    int y2 = ( rect_.y + y_val + MAIN_SIZE  - PlayWindow_Y - 1  ) / MAIN_SIZE ;

    if ( Map[y1][x1] == 1 || Map[y1][x2] == 1 || Map[y2][x1] == 1 || Map[y2][x2] == 1 )
    {
        rect_.x = rect_.x - x_val ;
        rect_.y = rect_.y - y_val;
    }
    rect_.x = rect_.x + x_val ;
    rect_.y = rect_.y + y_val;
    x_val = 0 ;
    y_val = 0 ;
}

void main_object::Show(SDL_Renderer* screen)
{

        switch ( direction_tank )
        {
        case LEFT :
        {
            LoadImg("img//tank_left.png",screen , MAIN_SIZE , MAIN_SIZE );
            break;
        }
        case RIGHT :
        {
            LoadImg("img//tank_right.png",screen , MAIN_SIZE , MAIN_SIZE );
            break;
        }
        case UP :
        {
            LoadImg("img//tank_up.png", screen , MAIN_SIZE , MAIN_SIZE );
            break;
        }
        case DOWN :
        {
            LoadImg("img//tank_down.png", screen , MAIN_SIZE , MAIN_SIZE );
            break;
        }

        }

        if ( is_living == true )
        {
            Render(screen);
        }
}



void main_object :: MakeBullet ( SDL_Renderer* screen , int MapMap[20][20]  )
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


void main_object :: RemoveBullet ( const int& idx )
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
