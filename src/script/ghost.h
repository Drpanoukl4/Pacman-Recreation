#include "../Utils/World.h"

class Ghost 
{

    public: 

        int Dir = 0;

        float gtimer = 0;
        int Chase_mode;

        float g_speed_X = 0;
        float g_speed_Y = 0;

        vec2D Ghost_pos = { 0, 0 };
        vec2D Corner = { 0, 0 };
        vec2D House = { 0, 0 };

        bool GoHome;
        bool canGo = false;
        bool Scatt;
        bool JustEyes = false;

    public:

        int Ghost_Type;
        int avaliable_Waysg;

        Ghost(int type) : Ghost_Type(type) {};

        bool Dir_s [4] {0};
        vec2D sTarget;

        void Move_Ghost(float time, World &pac_w);
        bool Check_coll(int i_Dir, vec2D Pos, float time, World &pac_w);


};