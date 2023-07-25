#include "GhostManager.h"

class Pacman 
{

    public: 
        float pacman_speed_X = 3.7f;
        float pacman_speed_Y = 0;
        int Dir = 0;

        vec2D player_pos = { 1, 1 };

    public:

        void Move_Coll (float time, World &pac_w);
        void Wrap(World &pac_w);

};