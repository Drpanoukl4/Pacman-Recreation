#include "utils.h"
#include <cstdint>

class World 
{

    public:

        int FieldWidth = 28;
        int FieldHeight = 31;
        int box_Width = 16;

        int Pellets_n;

        int Score = 0;

        bool GameOver = false;
        bool Mode = 0;
    
    public:

        std::vector<uint8_t> sWorld;

        void Initialize ();
        int GetTile (int x, int y);
        void SetTile (int x, int y, int tile);
        void Eat (int x, int y);

};

