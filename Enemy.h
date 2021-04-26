#ifndef Enemy_H_
#include Enemy_H_

#include "CommonFunction.h"
#include "TheatsObject.h"


class Enemy
{
public:
    Enemy();
    ~Enemy();
    void  Summon ();


private:
   vector <TheatsObject> tank_enemy ;



};


#endif // Enemy_H_
