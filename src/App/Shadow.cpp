
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "../script/pacman.h"

float ftartgetFrameTime = 1.0f / 6.0f;
float faccumulatedTime = 0.0f;
float tFrameTime = 1.0f / 6.0f;
float tTime = 0.0f;

int EatenGhost;

BoundingBox bPacman;

World pac_World;
Pacman player;

float timer = 0;

GhostManager manager;
Ghost Red(0);
Ghost Pink(1);
Ghost Orange(2);
Ghost Blue(3);

int PacXframe = 0;
int DeathFrame = 0;
int GhostXframe = 0;

int tti;

//World Texture//
olc::Sprite *Sprton;

class Shadow : public olc::PixelGameEngine
{

public:
	Shadow()
	{
		sAppName = "Example";
	}


public:

void TimerSprite( float fElapsedTime)
{

	tTime += fElapsedTime;
	if ( tTime >= tFrameTime ) 
	{

		tTime -= tFrameTime;
		fElapsedTime = tFrameTime;

		++tti %= 2;

	} 

}

float Spriteanim ( float fElapsedTime ) 
    {


        faccumulatedTime += fElapsedTime;
        if ( faccumulatedTime >= ftartgetFrameTime ) 
        {	
			faccumulatedTime -= ftartgetFrameTime;
			fElapsedTime = ftartgetFrameTime;
			if(!pac_World.GameOver) 
			{
			
				++PacXframe;
				++GhostXframe;
			}else 
			{
				DeathFrame ++;
			}

        } 

		if(DeathFrame >= 8) 
		{
			DeathFrame = 8;
		}

		if(PacXframe >= 2) 
		{

			PacXframe = 0;

		}

		if(GhostXframe >= 4) 
		{

			GhostXframe = 0;

		}

        return 5;

    }

	void Reset () 
	{
		pac_World.Initialize();
		pac_World.Score = 0;
		pac_World.Mode = 0;

		player.player_pos = {1, 1};

		for(auto &n : manager.Entities) 
		{
			switch(n.Ghost_Type) 
			{
				case 0:
					n.Ghost_pos = { (28 / 2) - 0.5f,  11};
					n.Corner = { 30,  0};
					n.House = { 15,  14};
					n.canGo = false;
					manager.red_p = 1;
				break;
				case 1:
					n.Ghost_pos = { 15,  14};
					n.Corner = { 0,  0};
					n.House = { 15,  14};
					n.canGo = false;
				break;
				case 2:
					n.Ghost_pos = { (28 / 2) - 0.5f,  14};
					n.Corner = { 0,  30};
					n.House = { 15,  14};
					n.canGo = false;
				break;
				case 3:
					n.Ghost_pos = { 12,  14};
					n.Corner = { 30,  30};
					n.House =  { 15,  14};
					n.canGo = false;
				break;
			}
		}

		player.Dir = 0;
		player.pacman_speed_X = 3.7f;
		DeathFrame = 0;
	}

	bool OnUserCreate() override
	{

		Sprton = new olc::Sprite("./Asset/Pacman.png");

		manager.Entities.push_back(Red);
		manager.Entities.push_back(Pink);
		manager.Entities.push_back(Orange);
		manager.Entities.push_back(Blue);
		Reset ();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		//Draawing
		TimerSprite( fElapsedTime);
		Spriteanim ( fElapsedTime );
		Clear(olc::BLACK);
		//Draw Blocks

		SetPixelMode(olc::Pixel::ALPHA);

		for(int x = 0; x < pac_World.FieldWidth; x ++) 
		{

			for(int y = 0; y < pac_World.FieldHeight; y ++) 
			{

				if(pac_World.GetTile(x, y) == 1)  //Wall
				{

					int fUp = 0; int fLeft = 0; int fRight = 0; int fDown = 0;

					if(pac_World.GetTile(x + 1, y) == 1) 
					{
						fRight = 3;
					}
					if(pac_World.GetTile(x - 1, y) == 1) 
					{
						fLeft = 7;
					}
					if(pac_World.GetTile(x, y - 1) == 1) 
					{
						fUp = 13;
					}
					if(pac_World.GetTile(x, y + 1) == 1) 
					{
						fDown = 11;
					}


					int Total = fRight + fLeft + fDown + fUp;

					switch(Total) 
					{

						case 24:
							DrawPartialSprite(x * pac_World.box_Width, y *  pac_World.box_Width, Sprton, 80, 0, 16, 16);
							break;
						case 16:
							DrawPartialSprite(x * pac_World.box_Width, y *  pac_World.box_Width, Sprton, 112, 0, 16, 16);
							break;
						case 20:
							DrawPartialSprite(x * pac_World.box_Width, y *  pac_World.box_Width, Sprton, 96, 0, 16, 16);
							break;
						case 14:
							DrawPartialSprite(x * pac_World.box_Width, y *  pac_World.box_Width, Sprton, 0, 16, 16, 16);
							break;
						case 18:
							DrawPartialSprite(x * pac_World.box_Width, y *  pac_World.box_Width, Sprton, 32, 16, 16, 16);
							break;
						case 10:
							DrawPartialSprite(x * pac_World.box_Width, y *  pac_World.box_Width, Sprton, 16, 16, 16, 16);
							break;
						case 7:
							DrawPartialSprite(x * pac_World.box_Width, y *  pac_World.box_Width, Sprton, 16, 16, 16, 16);
							break;
						case 3:
							DrawPartialSprite(x * pac_World.box_Width, y *  pac_World.box_Width, Sprton, 16, 16, 16, 16);
							break;
						case 23:
							DrawPartialSprite(x * pac_World.box_Width, y *  pac_World.box_Width, Sprton, 96, 112, 16, 16);
							break;
						case 21:
							DrawPartialSprite(x * pac_World.box_Width, y *  pac_World.box_Width, Sprton, 96, 96, 16, 16);
							break;
						case 27:
							DrawPartialSprite(x * pac_World.box_Width, y *  pac_World.box_Width, Sprton, 160, 112, 16, 16);
							break;
						case 31:
							DrawPartialSprite(x * pac_World.box_Width, y *  pac_World.box_Width, Sprton, 176, 112, 16, 16);
							break;

					}

					//FillRect(x * pac_World.box_Width, y * pac_World.box_Width, pac_World.box_Width, pac_World.box_Width, olc::BLUE);

				}else if( pac_World.GetTile(x, y) == 0 )
				{

					FillRect(x * pac_World.box_Width, y * pac_World.box_Width, pac_World.box_Width, pac_World.box_Width, olc::BLACK);
					FillCircle( x * pac_World.box_Width +  8, y * pac_World.box_Width +  8, 2, olc::Pixel(195, 136, 85) );

				}
				else if( pac_World.GetTile(x, y) == 4 )
				{

					if(tti == 0) 
					{
						FillRect(x * pac_World.box_Width, y * pac_World.box_Width, pac_World.box_Width, pac_World.box_Width, olc::BLACK);
						FillCircle( x * pac_World.box_Width +  8, y * pac_World.box_Width +  8, 6, olc::Pixel(195, 136, 85) );
					}else 
					{
						FillRect(x * pac_World.box_Width, y * pac_World.box_Width, pac_World.box_Width, pac_World.box_Width, olc::BLACK);
					}
					

				}
				else 
				{

					FillRect(x * pac_World.box_Width, y * pac_World.box_Width, pac_World.box_Width, pac_World.box_Width, olc::BLACK);

				}

			}

		}

		DrawPartialSprite(13 * pac_World.box_Width, 12 *  pac_World.box_Width, Sprton, 48, 16, 16, 16);
		DrawPartialSprite(14 * pac_World.box_Width, 12 *  pac_World.box_Width, Sprton, 48, 16, 16, 16);

		//Player Draw//

		float YDir;

			if(!pac_World.GameOver ) 
			{	
				switch(player.Dir) 
				{

					case 0:
						YDir = 0;
						break;
					case 1:
						YDir = 16;
						break;
					case 2:
						YDir = 48;
						break;
					case 3:
						YDir = 32;
						break;


				}
				DrawPartialSprite(player.player_pos.x * pac_World.box_Width, player.player_pos.y *  pac_World.box_Width, Sprton, PacXframe * pac_World.box_Width, 64 + YDir, 16, 16);

				//Ghost
				for(auto &n : manager.Entities) 
				{	

					switch(n.Ghost_Type)
					{

						case 0:
							if(n.Scatt) 
							{	
								if(timer > 400) 
								{
									if(tti == 0) 
									{
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 80, 16, 16);
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 64, 48, 16, 16);
									}else 
									{
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 128, 16, 16);
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 64, 128, 16, 16);
									}
								}else 
								{
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 80, 16, 16);
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 64, 48, 16, 16);
								}
								
							}else if(n.JustEyes) 
							{
								break;
							}else
							{
								DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 16, 16, 16);
							}	
						break;
						case 1:
							if(n.Scatt) 
							{
								if(timer > 400) 
								{
									if(tti == 0) 
									{
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 80, 16, 16);
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 64, 48, 16, 16);
									}else 
									{
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 128, 16, 16);
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 64, 128, 16, 16);
									}
								}else 
								{
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 80, 16, 16);
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 64, 48, 16, 16);
								}
							}else if(n.JustEyes) 
							{
								break;
							}else 
							{
								DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 64, 16, 16);
								
							}
						
						break;
						case 2:
						
							if(n.Scatt) 
							{
								if(timer > 400) 
								{
									if(tti == 0) 
									{
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 80, 16, 16);
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 64, 48, 16, 16);
									}else 
									{
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 128, 16, 16);
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 64, 128, 16, 16);
									}
								}else 
								{
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 80, 16, 16);
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 64, 48, 16, 16);
								}
							}else if(n.JustEyes) 
							{
								break;
							}else 
							{
								DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 48, 16, 16);
							}
						
						break;
						case 3:
						
							if(n.Scatt) 
							{
								if(timer > 400) 
								{
									if(tti == 0) 
									{
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 80, 16, 16);
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 64, 48, 16, 16);
									}else 
									{
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 128, 16, 16);
										DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 64, 128, 16, 16);
									}
								}else 
								{
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 80, 16, 16);
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 64, 48, 16, 16);
								}
							}else if(n.JustEyes) 
							{
								break;
							}else 
							{
								DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 80 + GhostXframe * pac_World.box_Width, 32, 16, 16);
							}
						
						break;

					}
					if(!n.Scatt) 
					{	
						if(n.JustEyes) 
						{

							switch(n.Dir) 
							{
								case 0:
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 16, 32, 16, 16);
									break;
								case 2:
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 0, 32, 16, 16);
									break;
								case 1:
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 32, 32, 16, 16);
									break;
								case 3: 
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 48, 32, 16, 16);
									break;
							}
							
						}else 
						{
							switch(n.Dir) 
							{
								case 0:
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 16, 48, 16, 16);
									break;
								case 2:
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 0, 48, 16, 16);
									break;
								case 1:
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 32, 48, 16, 16);
									break;
								case 3: 
									DrawPartialSprite( n.Ghost_pos.x * pac_World.box_Width, n.Ghost_pos.y *  pac_World.box_Width, Sprton, 48, 48, 16, 16);
									break;
							}
						}
						
					}

				}

			}else 
			{
				DrawPartialSprite(player.player_pos.x * pac_World.box_Width, player.player_pos.y *  pac_World.box_Width, Sprton, DeathFrame * pac_World.box_Width, 144, 16, 16);
			}
			
		SetPixelMode(olc::Pixel::NORMAL);

		FillRect(121, 100, 20, 113, olc::BLACK); FillRect(167, 104, 115, 21, olc::BLACK); FillRect(36, 436, 150, 25, olc::BLACK);
		FillRect(309, 100, 20, 113, olc::BLACK); FillRect(311, 393, 20, 19, olc::BLACK); FillRect(37, 342, 21, 19, olc::BLACK); FillRect(116, 342, 70, 19, olc::BLACK);
		FillRect(37, 100, 48, 19, olc::BLACK); FillRect(121, 393, 20, 19, olc::BLACK); FillRect(390, 342, 21, 19, olc::BLACK); FillRect(262, 342, 70, 19, olc::BLACK);
		FillRect(358, 100, 45, 19, olc::BLACK); FillRect(408, 393, 21, 19, olc::BLACK); FillRect(358, 344, 20, 68, olc::BLACK); FillRect(213, 348, 20, 14, olc::BLACK);
		FillRect(213, 55, 20, 19, olc::BLACK); FillRect(21, 393, 21, 19, olc::BLACK); FillRect(67, 344, 20, 68, olc::BLACK);  FillRect(45, 43, 40, 30, olc::BLACK);
		FillRect(213, 152, 20, 19, olc::BLACK); FillRect(214, 416, 19, 43, olc::BLACK); FillRect(167, 293, 115, 21, olc::BLACK); FillRect(125, 43, 55, 30, olc::BLACK);
		FillRect(167, 152, 20, 19, olc::BLACK); FillRect(167, 390, 115, 21, olc::BLACK); FillRect(310, 246, 20, 70, olc::BLACK); FillRect(267, 43, 59, 30, olc::BLACK);
		FillRect(265, 152, 20, 19, olc::BLACK); FillRect(262, 436, 150, 25, olc::BLACK); FillRect(117, 246, 20, 70, olc::BLACK); FillRect(360, 43, 45, 30, olc::BLACK);

		if(!pac_World.GameOver) 
		{
			
			if(GetKey(olc::Key::RIGHT).bHeld || GetKey(olc::Key::RIGHT).bPressed) 
			{

				player.pacman_speed_X = 3.7f;

			}
			if(GetKey(olc::Key::LEFT).bHeld || GetKey(olc::Key::LEFT).bPressed) 
			{

				player.pacman_speed_X = -3.7f;


			}
			if(GetKey(olc::Key::UP).bHeld || GetKey(olc::Key::UP).bPressed) 
			{

				player.pacman_speed_Y = -3.7f;


			}
			if(GetKey(olc::Key::DOWN).bHeld || GetKey(olc::Key::DOWN).bPressed) 
			{

				player.pacman_speed_Y = 3.7f;

			}

			//Movement && Collision//
			player.Move_Coll(fElapsedTime, pac_World);
			player.Wrap(pac_World);

			//Calculate Path//
			manager.Calculate_Path({player.player_pos.x, player.player_pos.y}, player.Dir, fElapsedTime, pac_World);

			for(auto &n : manager.Entities ) 
			{

				bPacman = { player.player_pos.x * 16, player.player_pos.y * 16, 10, 10 };
				BoundingBox Ghostb = { n.Ghost_pos.x * 16, n.Ghost_pos.y * 16, 10, 10 };

				//DrawRect( bPacman.x, bPacman.y, bPacman.width, bPacman.height, olc::RED );

				if(1 == bPacman.isCollided( bPacman, Ghostb ))
				{

					if(pac_World.Mode) 
					{

						n.GoHome = true;
						n.JustEyes = true;
						n.Scatt = 0;

					}else if(n.JustEyes)
					{
						continue;

					}
					else 
					{

						pac_World.GameOver = 1;

					}

				}

			}

		}

		manager.Gam (pac_World); 

		if( pac_World.GameOver == 1) 
		{

			DrawString( 10, 500, "Game Over", olc::WHITE );
			DrawString( 90, 510, "Press Enter", olc::WHITE );

			if(GetKey(olc::Key::ENTER).bPressed)
			{

				pac_World.GameOver = 0;
				Reset();

			}

		}


		if( pac_World.Mode == 1 ) 
		{

			timer += 50 * fElapsedTime;

			for(auto &n : manager.Entities) 
			{
				n.gtimer -= 10 * fElapsedTime;
				if(n.gtimer <= 0)
						n.gtimer = 0;

				if(n.JustEyes) 
				{	
					n.Scatt = 0;
					break;
				}

				if(n.gtimer == 0) 
				{

					n.Scatt = 1;
					n.gtimer = 300;

				}
			
			}			

			if(timer >= 450) 
			{
				pac_World.Mode = 0;

				for(auto &n : manager.Entities) 
				{

					n.Scatt = 0;

				}

				timer = 0;
			}

		}else 
		{

			for(auto &n : manager.Entities) 
			{
	
				n.gtimer = 0;

			}	

		}

		DrawString( 310, 500, "Score " + std::to_string(int(pac_World.Score)), olc::WHITE );

		for(int i = 0; i< 3; i ++) 
		{

			DrawPartialSprite(10 * (i * 3), 510, Sprton, 16, 64, 16, 16);
		}

		return true;
	}
};

int main()
{
	Shadow demo;
	if (demo.Construct(450, 532, 4, 4))
		demo.Start();

	return 0;
}
