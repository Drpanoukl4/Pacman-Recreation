#include "ghost.h"

class GhostManager
{

    public: 
        std::vector <Ghost> Entities;

    public:

        void vSolve_Rute(Ghost &current_Ghost, float time, World &pac_w); 
        void Calculate_Path(vec2D sTarget, int dir, float time, World &pac_w);
        void Gam (World &pac_w);

        float fDistance ( vec2D pA, vec2D pB );

        bool pink_p = true;
        bool oran_p = true;
        bool blue_p = true;
        bool red_p = false;

        static bool my_sort ( vec2D &a, vec2D &b ) 
        {
            return a.x < b.x;

        }


};