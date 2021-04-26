#ifndef Others_H_
#define Others_H_


#include "CommonFunction.h"
#include "BaseObject.h"
#include "TextObject.h"


class back_end
{
public:
    void LoadImg (SDL_Renderer* screen , TTF_Font* gFont , SDL_Color textColor );
    void LIVE ( string live , TTF_Font* gFont , SDL_Color textColor , SDL_Renderer* screen  );
    void TIME (  int time_game , TTF_Font* gFont , SDL_Color textColor , SDL_Renderer* screen  );
    void SCORE ( string score, TTF_Font* gFont , SDL_Color textColor , SDL_Renderer* screen   );
    void NUMBER_BULLET ( string number_bullet , TTF_Font* gFont , SDL_Color textColor , SDL_Renderer* screen   ) ;
private:
    base_object picture_live;
    base_object picture_oclock;
    TextObject score_text;
    TextObject number_bullet_text;
};
#endif // Others_H_
