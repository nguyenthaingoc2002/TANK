#include"CommonFunction.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "Time_FPS.h"
#include "TheatsObject.h"
#include "Explosion.h"
#include "TextObject.h"
#include "Menu.h"
#include "Others.h"
#include "Bonus_object.h"


back_end back_end_;
base_object game_over;
gift bonus;
explosion_object exp_enemy ;
explosion_object exp_main ;
base_object g_background;
TheatsObject tank_enemy1( PlayWindow_X  , PlayWindow_Y , DOWN , 0 , STEP_H , 2 );
TheatsObject tank_enemy2( PlayWindow_X + PlayWindow_SIZE - MAIN_SIZE  , PlayWindow_Y , LEFT , -STEP_H , 0 , 3 ) ;
TheatsObject tank_enemy3( PlayWindow_X + PlayWindow_SIZE - MAIN_SIZE  ,PlayWindow_Y + PlayWindow_SIZE - MAIN_SIZE , UP , 0 , -STEP_H , 5 ) ;
TheatsObject tank_enemy4( PlayWindow_X ,PlayWindow_Y + PlayWindow_SIZE - MAIN_SIZE , RIGHT , STEP_H , 0 , 4 ) ;
TileMap g_map ;
main_object tank;
ImpTimer fps_timer ;
SDL_Window* g_window = NULL ;
SDL_Renderer* g_screen = NULL ;
SDL_Event g_event ;
Mix_Chunk *explosion = NULL ;
Mix_Chunk *fire = NULL;
TTF_Font *gFont = NULL;
Menu gMenu ;
SDL_Color color_ = { 0,0,0 } ;
int score = 0 ;

bool InitData ()
{
    bool success = true ;
    int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO );
    if ( ret < 0 )
    {
        return false;
    }
    SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY , "1" ) ;

    g_window = SDL_CreateWindow( "Nguyen Thai Ngoc 20020208"
                                ,  0
                                ,  0
                                , SCREEN_WIDTH
                                , SCREEN_HEIGHT
                                , SDL_WINDOW_SHOWN);

    if ( g_window == NULL )
    {
        success =  false ;
    }
    else
    {
        g_screen = SDL_CreateRenderer (g_window , -1 , SDL_RENDERER_ACCELERATED ) ;
        if ( g_screen == NULL )
        {
            success = false ;
        }
        else
        {
            SDL_SetRenderDrawColor (g_screen , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR );
            int imgFlags = IMG_INIT_PNG ;
            if ( !(IMG_Init (imgFlags) &&  imgFlags) )
            {
                success = false ;
            }
            if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            {
                success = false;
            }
            if( TTF_Init() == -1 )
            {
                success = false;
            }
        }
    }

    return success;
}



bool LoadMedia ()
{
    bool ret = g_background.LoadImg( "img//background.png",g_screen , SCREEN_WIDTH , SCREEN_HEIGHT );
    if ( ret == false) return false ;
    gFont = TTF_OpenFont( "font//01.ttf", 300 ) ;
    g_map.Load_Map("img//map.txt");
    exp_enemy.LoadImg("img//exp3.png" , g_screen, MAIN_SIZE , MAIN_SIZE );
    exp_main.LoadImg("img//exp3.png" , g_screen, MAIN_SIZE , MAIN_SIZE );
    exp_enemy.set_clip();
    exp_main.set_clip();
    back_end_.LoadImg(g_screen , gFont , color_ );
    explosion = Mix_LoadWAV("sound//explosion.wav");
    fire = Mix_LoadWAV("sound//fire.wav");
    game_over.LoadImg("img//gameover.jpg" , g_screen , SCREEN_WIDTH  , SCREEN_HEIGHT);
    game_over.SetRect(0,0);
    return true ;
}






void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL ;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(  int argc, char* argv[]  )
{
    SDL_Rect PlayWindow;
    PlayWindow.h = PlayWindow.w = PlayWindow_SIZE ;
    PlayWindow.y =   PlayWindow_Y;
    PlayWindow.x =   PlayWindow_X;

    if ( InitData() == false ) return -1;
    if ( LoadMedia() == false ) return -2;

    bool is_quit = false ;
    //while ()
    gMenu.XuLy( g_event , g_screen , is_quit );

    while ( !is_quit  )
    {
        fps_timer.start();
        while( SDL_PollEvent(&g_event)  )
        {
            if ( g_event.type == SDL_QUIT )
            {
                is_quit = true;
            }
            if ( g_event.key.keysym.sym == SDLK_ESCAPE)
            {
                is_quit = true;
            }
            tank.HandleInputAction( g_event , g_screen , fire );
        }


        SDL_SetRenderDrawColor(g_screen,122,122,122,122 ) ;

        SDL_RenderClear (g_screen);
        g_background.Render(g_screen ) ;
        SDL_SetRenderDrawColor(g_screen , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR ) ;


        SDL_RenderFillRect(g_screen,&PlayWindow);


        g_map.Draw_Map(g_screen) ;



        tank.HandleMove(g_map.MapMap);
        if ( tank.getLiving() == true )
        {
            tank.Show(g_screen);
        }
        tank.MakeBullet( g_screen , g_map.MapMap  );








        if ( checkCollision (tank_enemy1.GetRect() , tank.GetRect() ) == true && tank.getLiving() == true  )
        {
            Mix_PlayChannel( -1 , explosion , 0 );
            exp_enemy.SetRect_( tank_enemy1.GetRect() );
            exp_enemy.set_frame(0);

            Mix_PlayChannel( -1 , explosion , 0 );
            exp_main.SetRect_( tank.GetRect() );
            exp_main.set_frame(0);

            tank_enemy1.setLiving(false);
            tank_enemy1.set_timeDie( SDL_GetTicks() );
            tank_enemy1.SetRect(0,0);

            tank.SetRect(0,0);
            tank.setLiving(false);
            tank.set_timeDie(SDL_GetTicks());
            tank.setLive(-1);
            if ( tank.getLive() == 0 )
            {
                is_quit = true ;
                SDL_RenderClear(g_screen);
                game_over.Render(g_screen);
                SDL_RenderPresent(g_screen);
                SDL_Delay(3000);
            }

        }

        if ( checkCollision (tank_enemy2.GetRect() , tank.GetRect()) == true && tank.getLiving() == true  )
        {
            Mix_PlayChannel( -1 , explosion , 0 );
            exp_enemy.SetRect_( tank_enemy1.GetRect() );
            exp_enemy.set_frame(0);

            Mix_PlayChannel( -1 , explosion , 0 );
            exp_main.SetRect_( tank.GetRect() );
            exp_main.set_frame(0);

            tank_enemy2.setLiving(false);
            tank_enemy2.set_timeDie( SDL_GetTicks() );
            tank_enemy2.SetRect(0,0);

            tank.SetRect(0,0);
            tank.setLiving(false);
            tank.set_timeDie(SDL_GetTicks());
            tank.setLive(-1);
            if ( tank.getLive() == 0 )
            {
                is_quit = true ;
                SDL_RenderClear(g_screen);
                game_over.Render(g_screen);
                SDL_RenderPresent(g_screen);
                SDL_Delay(3000);
            }

        }

        if ( checkCollision (tank_enemy3.GetRect() , tank.GetRect()) == true && tank.getLiving() == true )
        {
            Mix_PlayChannel( -1 , explosion , 0 );
            exp_enemy.SetRect_( tank_enemy1.GetRect() );
            exp_enemy.set_frame(0);

            Mix_PlayChannel( -1 , explosion , 0 );
            exp_main.SetRect_( tank.GetRect() );
            exp_main.set_frame(0);

            tank_enemy3.setLiving(false);
            tank_enemy3.set_timeDie( SDL_GetTicks() );
            tank_enemy3.SetRect(0,0);

            tank.SetRect(0,0);
            tank.setLiving(false);
            tank.set_timeDie(SDL_GetTicks());
            tank.setLive(-1);
            if ( tank.getLive() == 0 )
            {
                is_quit = true ;
                SDL_RenderClear(g_screen);
                game_over.Render(g_screen);
                SDL_RenderPresent(g_screen);
                SDL_Delay(3000);
            }

        }
        if ( checkCollision (tank_enemy4.GetRect() , tank.GetRect()) == true && tank.getLiving() == true )
        {
            Mix_PlayChannel( -1 , explosion , 0 );
            exp_enemy.SetRect_( tank_enemy1.GetRect() );
            exp_enemy.set_frame(0);

            Mix_PlayChannel( -1 , explosion , 0 );
            exp_main.SetRect_( tank.GetRect() );
            exp_main.set_frame(0);

            tank_enemy4.setLiving(false);
            tank_enemy4.set_timeDie( SDL_GetTicks() );
            tank_enemy4.SetRect(0,0);

            tank.SetRect(0,0);
            tank.setLiving(false);
            tank.set_timeDie(SDL_GetTicks());
            tank.setLive(-1);
            if ( tank.getLive() == 0 )
            {
                is_quit = true ;
                SDL_RenderClear(g_screen);
                game_over.Render(g_screen);
                SDL_RenderPresent(g_screen);
                SDL_Delay(3000);
            }

        }


        tank_enemy1.XuLy(g_screen , g_map.MapMap );
        tank_enemy2.XuLy(g_screen , g_map.MapMap );
        tank_enemy3.XuLy(g_screen , g_map.MapMap );
        tank_enemy4.XuLy(g_screen , g_map.MapMap );



        vector <bullet_object*> bullet_main = tank.get_bullet_list();
        for ( int i = 0 ; i < bullet_main.size() ; i++ )
        {
            bullet_object* bullet = bullet_main.at(i);
            if ( bullet != NULL )
            {
                if ( checkCollision ( bullet->GetRect() , tank_enemy1.GetRect()  ) == true  )
                {
                    Mix_PlayChannel( -1 , explosion , 0 );
                    exp_enemy.SetRect_( tank_enemy1.GetRect() );
                    exp_enemy.set_frame(0);

                    tank.RemoveBullet(i);
                    tank_enemy1.setLiving(false);
                    tank_enemy1.set_timeDie( SDL_GetTicks() );
                    tank_enemy1.SetRect(0,0);
                    score = score + 1 ;
                }
                if ( checkCollision ( bullet->GetRect() , tank_enemy2.GetRect()  ) == true  )
                {
                    Mix_PlayChannel( -1 , explosion , 0 );
                    exp_enemy.SetRect_( tank_enemy2.GetRect() );
                    exp_enemy.set_frame(0);
                    tank.RemoveBullet(i);
                    tank_enemy2.setLiving(false);
                    tank_enemy2.set_timeDie( SDL_GetTicks() );
                    tank_enemy2.SetRect(0,0);
                    score = score + 1 ;
                }
                if ( checkCollision ( bullet->GetRect() , tank_enemy3.GetRect()  ) == true  )
                {
                    Mix_PlayChannel( -1 , explosion , 0 );
                    exp_enemy.SetRect_( tank_enemy3.GetRect() );
                    exp_enemy.set_frame(0);
                    tank.RemoveBullet(i);
                    tank_enemy3.setLiving(false);
                    tank_enemy3.set_timeDie( SDL_GetTicks() );
                    tank_enemy3.SetRect(0,0);
                    score = score + 1 ;
                }
                if ( checkCollision ( bullet->GetRect() , tank_enemy4.GetRect()  ) == true  )
                {
                    Mix_PlayChannel( -1 , explosion , 0 );
                    exp_enemy.SetRect_( tank_enemy4.GetRect() );
                    exp_enemy.set_frame(0);
                    tank.RemoveBullet(i);
                    tank_enemy4.setLiving(false);
                    tank_enemy4.set_timeDie( SDL_GetTicks() );
                    tank_enemy4.SetRect(0,0);
                    score = score + 1 ;
                }
            }
        }

        vector <bullet_object*> bullet_enemy1 = tank_enemy1.get_bullet_list();
        for ( int i = 0 ; i  < bullet_enemy1.size() ; i++ )
        {
            bullet_object* bullet = bullet_enemy1.at(i);
            if ( bullet != NULL )
            {
                 if (  checkCollision ( bullet->GetRect() , tank.GetRect() ) == true )
                 {
                     Mix_PlayChannel( -1 , explosion , 0 );
                     exp_main.SetRect_( tank.GetRect() );
                     exp_main.set_frame(0);
                     tank.SetRect(0,0);
                     tank_enemy1.RemoveBullet(i) ;
                     tank.setLiving(false);
                     tank.set_timeDie(SDL_GetTicks());
                     tank.setLive(-1);
                     if ( tank.getLive() == 0 )
                     {

                        is_quit = true ;
                        SDL_RenderClear(g_screen);
                        game_over.Render(g_screen);
                        SDL_RenderPresent(g_screen);
                        SDL_Delay(3000);
                     }
                 }
            }
        }

        vector <bullet_object*> bullet_enemy2 = tank_enemy2.get_bullet_list();
        for ( int i = 0 ; i  < bullet_enemy2.size() ; i++ )
        {
            bullet_object* bullet = bullet_enemy2.at(i);
            if ( bullet != NULL )
            {
                 if (  checkCollision ( bullet->GetRect() , tank.GetRect() ) == true )
                 {
                     Mix_PlayChannel( -1 , explosion , 0 );
                     exp_main.SetRect_( tank.GetRect() );
                     exp_main.set_frame(0);
                     tank.SetRect(0,0);
                     tank_enemy2.RemoveBullet(i) ;
                     tank.setLiving(false);
                     tank.set_timeDie(SDL_GetTicks());
                     tank.setLive(-1);
                     if ( tank.getLive() == 0 )
                     {
                         is_quit = true ;
                         SDL_RenderClear(g_screen);
                        game_over.Render(g_screen);
                        SDL_RenderPresent(g_screen);
                        SDL_Delay(3000);
                     }
                }
            }
        }


        vector <bullet_object*> bullet_enemy3 = tank_enemy3.get_bullet_list();
        for ( int i = 0 ; i  < bullet_enemy3.size() ; i++ )
        {
            bullet_object* bullet = bullet_enemy3.at(i);
            if ( bullet != NULL )
            {
                 if (  checkCollision ( bullet->GetRect() , tank.GetRect() ) == true )
                 {
                     Mix_PlayChannel( -1 , explosion , 0 );
                     exp_main.SetRect_( tank.GetRect() );
                     exp_main.set_frame(0);
                     tank.SetRect(0,0);
                     tank_enemy3.RemoveBullet(i) ;
                     tank.setLiving(false);
                     tank.set_timeDie(SDL_GetTicks());
                     tank.setLive(-1);
                     if ( tank.getLive() == 0 )
                     {
                         is_quit = true ;
                         SDL_RenderClear(g_screen);
                        game_over.Render(g_screen);
                        SDL_RenderPresent(g_screen);
                        SDL_Delay(3000);
                     }
                }
            }
        }

        vector <bullet_object*> bullet_enemy4 = tank_enemy4.get_bullet_list();
        for ( int i = 0 ; i  < bullet_enemy4.size() ; i++ )
        {
            bullet_object* bullet = bullet_enemy4.at(i);
            if ( bullet != NULL )
            {
                 if (  checkCollision ( bullet->GetRect() , tank.GetRect() ) == true )
                 {
                     Mix_PlayChannel( -1 , explosion , 0 );
                     exp_main.SetRect_( tank.GetRect() );
                     exp_main.set_frame(0);
                     tank.SetRect(0,0);
                     tank_enemy4.RemoveBullet(i) ;
                     tank.setLiving(false);
                     tank.set_timeDie(SDL_GetTicks());
                     tank.setLive(-1);
                     if ( tank.getLive() == 0 )
                     {
                         is_quit = true ;
                         SDL_RenderClear(g_screen);
                        game_over.Render(g_screen);
                        SDL_RenderPresent(g_screen);
                        SDL_Delay(3000);
                     }
                     }
                 }
            }


        //tank_enemy1.HandleMove(g_map.MapMap);
        if (tank_enemy1.getLiving() == true )
        {
            tank_enemy1.Show(g_screen);
        }


        //tank_enemy2.HandleMove(g_map.MapMap);
        if (tank_enemy2.getLiving() == true )
        {
            tank_enemy2.Show(g_screen);
        }


        //tank_enemy3.HandleMove(g_map.MapMap);
        if (tank_enemy3.getLiving() == true )
        {
            tank_enemy3.Show(g_screen);
        }

        if (tank_enemy4.getLiving() == true )
        {
            tank_enemy4.Show(g_screen);
        }


        tank_enemy1.MakeBullet(g_screen , g_map.MapMap );
        tank_enemy2.MakeBullet(g_screen , g_map.MapMap );
        tank_enemy3.MakeBullet(g_screen , g_map.MapMap );
        tank_enemy4.MakeBullet(g_screen , g_map.MapMap );


        bonus.gogo(g_map.MapMap);
        bonus.LoadImg_(g_screen);
        bonus.Show(g_screen);

        if ( checkCollision ( tank.GetRect() , bonus.GetRect() ) == true )
        {
            bonus.setLiving(false);
            bonus.set_timeDie(SDL_GetTicks());
            if ( bonus.get_type_gift() == 1 ) tank.setLive(1);
            if ( bonus.get_type_gift() == 2 ) tank.MAX_NUMBER_BULLET_MAIN++;
        }


        if (  SDL_GetTicks() - tank.get_timeDie()  > 3000 && tank.getLiving() == false )
        {
            tank.setLiving(true);
            tank.SetRect( PlayWindow_X + 300 , PlayWindow_Y + PlayWindow_SIZE - MAIN_SIZE - 300 );
        }
        if (  SDL_GetTicks() - tank_enemy1.get_timeDie() > 3000 && tank_enemy1.getLiving() == false )
        {
            tank_enemy1.setLiving(true);
            tank_enemy1.SetRect( PlayWindow_X , PlayWindow_Y );
        }

        if ( SDL_GetTicks() - tank_enemy2.get_timeDie() > 3000 && tank_enemy2.getLiving() == false )
        {
            tank_enemy2.setLiving(true);
            tank_enemy2.SetRect( PlayWindow_X + PlayWindow_SIZE - MAIN_SIZE  , PlayWindow_Y  );
        }

        if ( SDL_GetTicks() - tank_enemy3.get_timeDie() > 3000 && tank_enemy3.getLiving() == false  )
        {
            tank_enemy3.setLiving(true);
            tank_enemy3.SetRect( PlayWindow_X + PlayWindow_SIZE - MAIN_SIZE  ,PlayWindow_Y + PlayWindow_SIZE - MAIN_SIZE );
        }

        if ( SDL_GetTicks() - tank_enemy4.get_timeDie() > 3000 && tank_enemy4.getLiving() == false  )
        {
            tank_enemy4.setLiving(true);
            tank_enemy4.SetRect( PlayWindow_X ,PlayWindow_Y + PlayWindow_SIZE - MAIN_SIZE );
        }
        exp_enemy.Show_(g_screen);
        exp_main.Show_(g_screen);


        back_end_.LIVE(to_string(tank.getLive()) , gFont , color_ , g_screen  );
        back_end_.SCORE(to_string(score) , gFont , color_ , g_screen   );
        back_end_.NUMBER_BULLET(to_string(tank.MAX_NUMBER_BULLET_MAIN) , gFont , color_ , g_screen );
        back_end_.TIME( SDL_GetTicks() , gFont , color_ , g_screen );
        SDL_RenderPresent(g_screen);



        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000 / FPS ;

        if ( real_imp_time < time_one_frame )
        {
            int delay_time = time_one_frame - real_imp_time ;
            if ( delay_time >= 0 ) SDL_Delay(delay_time);
        }

    }


    close();


    return 0;
}
