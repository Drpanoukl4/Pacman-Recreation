#include "GhostManager.h"
#include <list>
#include <algorithm>

float GhostManager::fDistance ( vec2D pA, vec2D pB )
{

    return sqrtf( (pA.x - pB.x) * (pA.x - pB.x) + (pA.y - pB.y) * (pA.y - pB.y));

}

void GhostManager::vSolve_Rute( Ghost &current_Ghost, float time, World &pac_w)
{

    vec2D dis_vec;

    float &CurposX = current_Ghost.Ghost_pos.x;
    float &CurposY = current_Ghost.Ghost_pos.y;

    float posX = current_Ghost.Ghost_pos.x + current_Ghost.g_speed_X * time;
    float posY = current_Ghost.Ghost_pos.y + current_Ghost.g_speed_Y * time;

    current_Ghost.Dir_s[0] = current_Ghost.Check_coll (0,{CurposX + 3.7f * time, CurposY}, time, pac_w);
    current_Ghost.Dir_s[1] = current_Ghost.Check_coll (1,{CurposX, CurposY - 3.7f * time}, time, pac_w);
    current_Ghost.Dir_s[2] = current_Ghost.Check_coll (2,{CurposX - 3.7f * time, CurposY}, time, pac_w);
    current_Ghost.Dir_s[3] = current_Ghost.Check_coll (3,{CurposX, CurposY + 3.7f * time}, time, pac_w);

    std::vector <vec2D> distances;
    distances.clear();

    int Optimal_Dir;
    int avaliable_Ways = 0;

    for(int i = 0; i < 4; i ++) 
    {

        if(i == ((current_Ghost.Dir + 2) % 4 ))
        {
            continue;
        }else if( current_Ghost.Dir_s[i] == 0 ) 
        {

            avaliable_Ways += 1;
            current_Ghost.avaliable_Waysg = avaliable_Ways;

            switch(i)
            {

                case 0:

                    dis_vec = {CurposX + 3.7f, CurposY }; 

                break;
                case 1:

                    dis_vec = {CurposX, CurposY - 3.7f}; 

                break;
                case 2:

                    dis_vec = {CurposX - 3.7f, CurposY};

                break;
                case 3:

                    dis_vec = {CurposX, CurposY + 3.7f}; 

                break;

            }

            vec2D dis = {fDistance ( dis_vec, current_Ghost.sTarget ), float(i)};
            distances.push_back(dis);

            std::sort( distances.begin(), distances.end(), my_sort );

            Optimal_Dir = distances[0].y;
        }

    }
    
    switch(current_Ghost.Chase_mode)
    {

        case 0:

            if(avaliable_Ways > 1) 
            {
                current_Ghost.Dir = Optimal_Dir;  
            }else 
            {   
                if(avaliable_Ways == 0) 
                {
                    current_Ghost.Dir = (current_Ghost.Dir + 2) % 4;
                }else 
                {
                    current_Ghost.Dir = Optimal_Dir;  
                }
            }
            break;
        case 1:

            if(avaliable_Ways > 1) 
            {
                current_Ghost.Dir = Optimal_Dir;  
            }else 
            {   
                if(avaliable_Ways == 0) 
                {
                    current_Ghost.Dir = current_Ghost.Dir;
                }else 
                {
                    current_Ghost.Dir = Optimal_Dir;  
                }
            }
        break;


    }

    current_Ghost.g_speed_X = 0;
    current_Ghost.g_speed_Y = 0;

    if(current_Ghost.Scatt) 
    {

        switch(current_Ghost.Dir) 
        {

            case 0:
                current_Ghost.g_speed_X = 2.7f;

            break;
            case 2:
                current_Ghost.g_speed_X = -2.7f;

            break;
            case 3:
                current_Ghost.g_speed_Y = 2.7f;

            break;
            case 1:
                current_Ghost.g_speed_Y = -2.7f;

            break;

        }

    }else if(current_Ghost.JustEyes) 
    {

        switch(current_Ghost.Dir) 
        {

            case 0:
                current_Ghost.g_speed_X = 7.7f;

            break;
            case 2:
                current_Ghost.g_speed_X = -7.7f;

            break;
            case 3:
                current_Ghost.g_speed_Y = 7.7f;

            break;
            case 1:
                current_Ghost.g_speed_Y = -7.7f;

            break;

        }

    }else 
    {
        switch(current_Ghost.Dir) 
        {

            case 0:
                current_Ghost.g_speed_X = 3.7f;

            break;
            case 2:
                current_Ghost.g_speed_X = -3.7f;

            break;
            case 3:
                current_Ghost.g_speed_Y = 3.7f;

            break;
            case 1:
                current_Ghost.g_speed_Y = -3.7f;

            break;

        }
    }


    current_Ghost.Move_Ghost(time, pac_w);

    if(current_Ghost.Dir == 2) 
    {
        if( pac_w.GetTile( posX, CurposY ) == 1 || pac_w.GetTile( posX, CurposY + 0.9f ) == 1) 
        {
            CurposX = int(CurposX + 1);
        }
    } else if(current_Ghost.Dir == 0) 
    {
        if( pac_w.GetTile( posX + 1, CurposY ) == 1 || pac_w.GetTile( posX + 1, CurposY + 0.9f ) == 1) 
        {
            CurposX = int(CurposX);
        }
    }
    
    if(current_Ghost.Dir == 1) 
    {
        if( pac_w.GetTile( posX, posY ) == 1 || pac_w.GetTile( posX + 0.9f, posY) == 1) 
        {
            CurposY = int(CurposY + 1);
        }
    } else if(current_Ghost.Dir == 3)
    {
        if( pac_w.GetTile( posX, posY + 1 ) == 1 || pac_w.GetTile( posX + 0.9f, posY + 1 ) == 1) 
        {
            CurposY = int(CurposY);
        }
    }

    if(CurposY > 25.9f && CurposY < 26)
        CurposY = 26;
    if(CurposX > 25.9f && CurposX < 26)
        CurposX = 26;
    if(CurposX > 11.9f && CurposX < 12)
        CurposX = 12;
    if(CurposX > 5.9f && CurposX < 6)
        CurposX = 6;
    if(CurposX > 8.9f && CurposX < 9)
        CurposX = 9;
    if(CurposY > 28.9f && CurposY < 29)
        CurposY = 29;
    if(CurposY > 4.9f && CurposY < 5)
        CurposY = 5;
    if(CurposY > 19.9f && CurposY < 20)
        CurposY = 20;
    if(CurposX > 17.9f && CurposX < 18)
        CurposX = 18;
}

void GhostManager::Gam (World &pac_w) 
{

    if(pac_w.GameOver == 1) 
    {

        pink_p = true;
        oran_p = true;
        blue_p = true;

    }

}

void GhostManager::Calculate_Path(vec2D pac_Pos, int dir, float time, World &pac_w) 
{   

    for( auto &n : Entities ) 
    {


        switch(n.Ghost_Type)
        {

            case 0:

                if(n.GoHome) 
                {
                    n.sTarget = n.House;
                    n.canGo = true;
                    if(fDistance ( n.Ghost_pos, n.House ) < 2) 
                    {   
                        n.Ghost_pos = n.House;
                        n.GoHome = false;
                        red_p  = true;
                    }else 
                    {    
                        break;
                    }
                }
                if(red_p )
                {
                    if(pac_w.Score >= 0)
                    {   
                        n.Chase_mode = 0;
                        n.canGo = true;
                        if(n.canGo) {
                            n.sTarget = { (28 / 2),  11};
                            if(fDistance ( n.Ghost_pos, n.sTarget ) < 1) 
                            {   
                                n.canGo = false;
                                red_p  = false;
                                n.Ghost_pos = { (28 / 2),  11};
                                n.Chase_mode = 1;
                            }
                        } 
                    }else 
                    {   
                        n.Chase_mode = 0;
                        n.sTarget = n.House;
                    }
                }
                if(n.canGo == false) 
                {   
                    n.JustEyes = false;
                    if(n.Scatt == 0) 
                    {
                        n.sTarget = {pac_Pos.x, pac_Pos.y};
                    }else 
                    {   
                        n.sTarget = n.Corner;
                    }
                }
                
            break;
            case 1:

                if(n.GoHome) 
                {
                    n.sTarget = n.House;
                    n.canGo = true;

                    if(fDistance ( n.Ghost_pos, n.House ) < 2) 
                    {   
                        n.GoHome = false;
                        n.Ghost_pos = n.House;
                        pink_p  = true;

                    }else 
                    {    
                        break;
                    }
                }

                if(pink_p )
                {
                    if(pac_w.Score > 165)
                    {   

                        n.Chase_mode = 0;
                        n.canGo = true;
                        if(n.canGo) {
                            n.sTarget = { (28 / 2),  11};
                            if(fDistance ( n.Ghost_pos, n.sTarget ) < 1) 
                            {   
                                n.canGo = false;
                                pink_p  = false;
                                n.Ghost_pos = { (28 / 2),  11};
                                n.Chase_mode = 1;
                            }
                        }

                        
                    }else 
                    {   
                        n.Chase_mode = 0;
                        n.sTarget = n.House;
                    }
                }

                if(n.canGo == false) 
                {   
                    n.JustEyes = false;

                    if(n.Scatt == 0) 
                    {
                        switch(dir) 
                        {
                            case 0:
                                n.sTarget = {pac_Pos.x - 4, pac_Pos.y};
                            break;
                            case 1:
                                n.sTarget = {pac_Pos.x + 4, pac_Pos.y};
                            break;
                            case 2:
                                n.sTarget = {pac_Pos.x, pac_Pos.y + 4};
                            break;
                            case 3:
                                n.sTarget = {pac_Pos.x, pac_Pos.y - 4};
                            break;
                        }
                    }else 
                    {   
                        n.sTarget = n.Corner;
                    }
                }

            break;
            case 2:
                if(n.GoHome) 
                {
                    n.sTarget = n.House;
                    n.canGo = true;

                    if(fDistance ( n.Ghost_pos, n.House ) < 2) 
                    {   
                        n.GoHome = false;
                        oran_p  = true;
                        n.Ghost_pos = n.House;
                    }else 
                    {    
                        break;
                    }
                }
                if(oran_p )
                {
                    if(pac_w.Score > 325)
                    {   
                        n.Chase_mode = 0;
                        n.canGo = true;
                        if(n.canGo) {
                            n.sTarget = { (28 / 2),  11};
                            if(fDistance ( n.Ghost_pos, n.sTarget ) < 1) 
                            {   
                                n.canGo = false;
                                n.Dir = (n.Dir + 2) % 4;
                                oran_p  = false;
                                n.Ghost_pos = { (28 / 2),  11};
                                n.Chase_mode = 1;
                            }
                        }
                    }else 
                    {   
                        n.Chase_mode = 0;
                        n.sTarget = n.House;
                    }
                }

                if(n.canGo == false) 
                {   
                    n.JustEyes = false;
                    if(n.Scatt == 0) 
                    {
                        n.sTarget = {pac_Pos.x, pac_Pos.y};
                        if(fDistance(n.Ghost_pos, n.sTarget) < 4) 
                        {
                            n.sTarget = n.Corner;
                        }
                    }else 
                    {   
                        n.sTarget = n.Corner;
                    }
                }
            break;
            case 3: 

                if(n.GoHome) 
                {
                    n.sTarget = n.House;
                    n.canGo = true;

                    if(fDistance ( n.Ghost_pos, n.House ) < 2) 
                    {   
                        n.GoHome = false;
                        n.Ghost_pos = n.House;
                        blue_p  = true;

                    }else 
                    {    
                        break;
                    }
                }

                if(blue_p )
                {
                    if(pac_w.Score > 225)
                    {   

                        n.Chase_mode = 0;
                        n.canGo = true;
                        if(n.canGo) {
                            n.sTarget = { (28 / 2),  11};
                            if(fDistance ( n.Ghost_pos, n.sTarget ) < 1) 
                            {   
                                n.canGo = false;
                                blue_p  = false;
                                n.Ghost_pos = { (28 / 2),  11};
                                n.Chase_mode = 1;
                            }
                        }

                        
                    }else 
                    {   
                        n.Chase_mode = 0;
                        n.sTarget = n.House;
                    }
                }

                if(n.canGo == false) 
                {   
                    n.JustEyes = false;

                    if(n.Scatt == 0) 
                    {
                        switch(dir) 
                        {
                            case 0:
                                n.sTarget = {pac_Pos.x - 2, pac_Pos.y};
                            break;
                            case 1:
                                n.sTarget = {pac_Pos.x + 2, pac_Pos.y};
                            break;
                            case 2:
                                n.sTarget = {pac_Pos.x, pac_Pos.y + 2};
                            break;
                            case 3:
                                n.sTarget = {pac_Pos.x, pac_Pos.y - 2};
                            break;
                        }
                    }else 
                    {   
                        n.sTarget = n.Corner;
                    }
                }

            break;
        }

        vSolve_Rute(n, time, pac_w);

    }

}
