#ifndef TheatsObject_H_
#define TheatsObject_H_
#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"


class TheatsObject : public base_object
{
public:
    TheatsObject(int x_ , int y_ , DIRECTION direction_tank_ , int x_val_ , int y_val_ , int number_tank_ ) ;
    ~TheatsObject();
    void HandleMove();
    bool Check ( int x , int y );
    void Show(SDL_Renderer* screen);
    void MakeBullet ( SDL_Renderer* screen , int MapMap[20][20] ) ;
    void XuLy (SDL_Renderer* screen ,  int Map[20][20] ) ;
    void setGoing ( bool going_ ) { going = going_ ; }
    void setVal ( int x_val_ , int y_val_ ) { x_val = x_val_ , y_val = y_val_ ;}
    void RemoveBullet (const int& idx );
    vector <bullet_object*> get_bullet_list () const {return p_bullet_list_ ;}
    void setLiving ( bool is_living_ ) { is_living = is_living_ ;}
    bool getLiving () {return is_living ;}
    void set_timeDie ( int timeDie_ ) { timeDie = timeDie_ ;}
    int get_timeDie () { return timeDie ; }
private:
    vector <bullet_object*> p_bullet_list_ ;
    int x_val ;
    int y_val ;
    int timeDie;
    unsigned int bullet_time = 0  ;
    DIRECTION direction_tank   ;
    bool going = true ;
    bool is_living = true ;
    bool direction_bool [4] ;
    int number_tank ;
};






#endif // TheatsObject_H_
