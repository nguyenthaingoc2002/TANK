#ifndef Bonus_object_H_
#define Bonus_object_H_

#include"BaseObject.h"
#include"CommonFunction.h"



class gift : public base_object
{
public:
    gift();
    ~gift();
    void gogo (int MapMap[20][20]);
    void LoadImg_(SDL_Renderer* screen );
    void Show(SDL_Renderer* screen);
    void set_timeDie ( int timeDie_ ) { timeDie = timeDie_ ;}
    int get_timeDie () { return timeDie ; }
    void setLiving ( bool is_living_ ) { is_living = is_living_ ;}
    bool getLiving () {return is_living ;}
    int get_type_gift () { return type_gift; }
private:
    int type_gift;
    int timeDie = 0 ;
    bool is_living = false;
};


#endif // Bonus_object_H_
