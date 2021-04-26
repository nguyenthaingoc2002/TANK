#ifndef MainObject_H_
#define MainObject_H_

#include"CommonFunction.h"
#include"BaseObject.h"
#include "BulletObject.h"






class main_object : public base_object
{
public:
    main_object();
    ~main_object();


    void HandleInputAction ( SDL_Event event , SDL_Renderer* screen , Mix_Chunk* fire );
    void HandleMove(int Map[20][20]);
    void Show(SDL_Renderer* screen);
    void set_bullet_list ( vector <bullet_object*> bullet_list )
    {
        p_bullet_list_ = bullet_list ;
    }
    vector <bullet_object*> get_bullet_list () const {return p_bullet_list_ ;}
    void MakeBullet ( SDL_Renderer* screen , int MapMap[20][20]  ) ;
    void RemoveBullet (const int& idx );
    void setLiving ( bool is_living_ ) { is_living = is_living_ ;}
    bool getLiving () {return is_living ;}
    void set_timeDie ( int timeDie_ ) { timeDie = timeDie_ ;}
    int get_timeDie () { return timeDie ; }
    void setLive ( int live_ ) { live = live + live_ ;}
    int getLive () { return live ;}
    int MAX_NUMBER_BULLET_MAIN = 1;
private:
    vector <bullet_object*> p_bullet_list_ ;
    int x_val ;
    int y_val ;
    int timeDie ;
    int live = 3 ;
    DIRECTION direction_tank ;
    bool is_living = true ;

};

#endif // MainObject_H_
