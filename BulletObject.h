#ifndef BulletObject_H_
#define BulletObject_H_
#include "BaseObject.h"
#include "BulletObject.h"
#include"CommonFunction.h"



class bullet_object : public base_object
{


public:
    bullet_object();
    ~bullet_object();

    void set_x_val ( const int& xVal ) {x_val_ = xVal ; }
    void set_y_val ( const int& yVal ) {y_val_ = yVal ; }
    int get_x_val () const { return x_val_ ;}
    int get_y_val () const { return y_val_ ;}
    void set_is_move ( const bool& isMove ) {is_move_ = isMove ; }
    bool get_is_move () const { return is_move_ ; }
    void handle_move ( int MapMap[20][20] ) ;



private:

     int x_val_ ;
     int y_val_ ;
     bool is_move_;


};


#endif // BulletObject_H_
