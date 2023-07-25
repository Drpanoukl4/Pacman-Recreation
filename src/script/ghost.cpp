#include "ghost.h"

void Ghost::Move_Ghost(float time, World &pac_w) 
{

    float newplayer_posx = Ghost_pos.x + (g_speed_X * time);
    float newplayer_posy = Ghost_pos.y + (g_speed_Y * time);

    Ghost_pos.x = newplayer_posx;
    Ghost_pos.y = newplayer_posy;

    if( Ghost_pos.x > 28 ) 
    {

        Ghost_pos.x = Ghost_pos.x - 28;

    }else if( Ghost_pos.x < 0)
    {

        Ghost_pos.x = Ghost_pos.x + 28;
            
    }
}

bool Ghost::Check_coll (int i_Dir, vec2D Pos, float time, World &pac_w) 
{

    float x = Pos.x;
    float y = Pos.y;

    switch(i_Dir) 
    {

        case 2:
            //LEFT

            if(!canGo) 
            {
                if(pac_w.GetTile(x, y) == 1 || pac_w.GetTile( x, y + 0.9f ) == 1 || pac_w.GetTile(x, y) == 5 || pac_w.GetTile( x, y + 0.9f ) == 5  || pac_w.GetTile(x, y) == 6 || pac_w.GetTile( x, y + 0.9f ) == 6) 
                {  
                    return 1;
                }else 
                {
                    return 0;
                }
            }

            if(pac_w.GetTile(x, y) == 1 || pac_w.GetTile( x, y + 0.9f ) == 1 || pac_w.GetTile(x, y) == 5 || pac_w.GetTile( x, y + 0.9f ) == 5) 
            {  
                return 1;
            }else 
            {
                return 0;

            }
        break;
        case 0:
            //RIGHT
            if(!canGo) 
            {
                if(pac_w.GetTile(x + 1, y) == 1 || pac_w.GetTile( x + 1, y + 0.9f ) == 1 || pac_w.GetTile(x + 1, y) == 5 || pac_w.GetTile( x + 1, y + 0.9f ) == 5 || pac_w.GetTile(x + 1, y) == 6 || pac_w.GetTile( x + 1, y + 0.9f ) == 6) 
                {  
                    return 1;
                }else 
                {
                    return 0;
                }

            }
            if(pac_w.GetTile(x + 1, y) == 1 || pac_w.GetTile( x + 1, y + 0.9f ) == 1 || pac_w.GetTile(x + 1, y) == 5 || pac_w.GetTile( x + 1, y + 0.9f ) == 5) 
            {   
                return 1;
            }else 
            {
                return 0;
            }
        break;
        case 1:

            if(!canGo) 
            {
                if(pac_w.GetTile(x, y) == 1 || pac_w.GetTile( x + 0.9f, y ) == 1 || pac_w.GetTile(x, y) == 5 || pac_w.GetTile( x + 0.9f, y ) == 5 || pac_w.GetTile(x, y) == 6 || pac_w.GetTile( x + 0.9f, y ) == 6) 
                {  
                    return 1;
                }else 
                {
                    return 0;
                }

            }
            //UP
            if(pac_w.GetTile(x, y) == 1 || pac_w.GetTile( x + 0.9f, y ) == 1 || pac_w.GetTile(x, y) == 5 || pac_w.GetTile( x + 0.9f, y ) == 5) 
            {   
                return 1;
            }else 
            {
                return 0;
            }
        break;
        case 3:
            //DOWN
            if(!canGo) 
            {
                if(pac_w.GetTile(x, y + 1 ) == 1 || pac_w.GetTile( x + 0.9f, y + 1) == 1 || pac_w.GetTile(x, y + 1) == 5 || pac_w.GetTile( x + 0.9f, y + 1) == 5 || pac_w.GetTile(x, y + 1) == 6 || pac_w.GetTile( x + 0.9f, y + 1) == 6) 
                {  
                    return 1;
                }else 
                {
                    return 0;
                }

            }
            if(pac_w.GetTile(x, y + 1 ) == 1 || pac_w.GetTile( x + 0.9f, y + 1) == 1 || pac_w.GetTile(x, y + 1) == 5 || pac_w.GetTile( x + 0.9f, y + 1) == 5) 
            {   
                return 1;
            }else 
            {
                return 0;
            }
        break;
    }

    return 1;

}