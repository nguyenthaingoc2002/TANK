#ifndef GameMap_H_
#define GameMap_H_

#include "CommonFunction.h"
#include "BaseObject.h"





class TileMap
{
public:
    int MapMap[20][20];
    TileMap() {;}
    ~TileMap() {;}
    void Load_Map ( string name );
    void Draw_Map (SDL_Renderer* screen );
private:
    base_object wall ;

};





#endif // GameMap_H_
