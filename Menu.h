#ifndef Menu_H_
#define Menu_H_

#include"BaseObject.h"
#include"CommonFunction.h"


class Menu
{
public:
    Menu();
    ~Menu();
    void XuLy ( SDL_Event event , SDL_Renderer* screen , bool &is_quit   );
private:
    base_object menu_ ;
};




#endif // Menu_H_
