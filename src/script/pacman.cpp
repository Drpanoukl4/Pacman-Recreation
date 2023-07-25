#include "pacman.h"

void Pacman::Move_Coll (float time, World &pac_w)
{

        float newplayer_posx = player_pos.x + pacman_speed_X * time;
		float newplayer_posy = player_pos.y + pacman_speed_Y * time;

		if(pacman_speed_X < 0) 
		{

			if( pac_w.GetTile( newplayer_posx, player_pos.y ) == 1 || pac_w.GetTile( newplayer_posx, player_pos.y + 0.9f ) == 1) 
			{

				newplayer_posx = int(newplayer_posx + 1);
				pacman_speed_X = 0;

			}
			//Pellets
			pac_w.Eat (newplayer_posx, player_pos.y);

		} else 
		{

			if( pac_w.GetTile( newplayer_posx + 1, player_pos.y ) == 1 || pac_w.GetTile( newplayer_posx + 1, player_pos.y + 0.9f ) == 1) 
			{

				newplayer_posx = int(newplayer_posx);
				pacman_speed_X = 0;

			}
			//Pellets
			pac_w.Eat (newplayer_posx, player_pos.y);
			
		}

		if(pacman_speed_Y < 0) 
		{

			if( pac_w.GetTile( newplayer_posx, newplayer_posy ) == 1 || pac_w.GetTile( newplayer_posx + 0.9f, newplayer_posy) == 1) 
			{

				newplayer_posy = int(newplayer_posy + 1);
				pacman_speed_Y = 0;

			}



		} else 
		{

			if( pac_w.GetTile( newplayer_posx , newplayer_posy + 1 ) == 1 || pac_w.GetTile( newplayer_posx + 0.9f, newplayer_posy + 1 ) == 1) 
			{

				newplayer_posy = int(newplayer_posy);
				pacman_speed_Y = 0;

			}

		}
		
		//Pellets
		pac_w.Eat (newplayer_posx, newplayer_posy);

		player_pos.x = newplayer_posx;
		player_pos.y = newplayer_posy;

		if(pacman_speed_X == -3.7f) 
		{

			Dir = 1;

		} else if(pacman_speed_X == 3.7f)
		{

			Dir = 0;
			
		}

		if(pacman_speed_Y == -3.7f) 
		{

			Dir = 3;


		} else if(pacman_speed_Y == 3.7f) 
		{

			Dir = 2;

		}
		

}

void Pacman::Wrap(World &pac_w) 
{

    if( player_pos.x > pac_w.FieldWidth ) 
    {

        player_pos.x = player_pos.x - pac_w.FieldWidth;

    }else if( player_pos.x < 0)
    {

        player_pos.x = player_pos.x + pac_w.FieldWidth;
            
    }

}