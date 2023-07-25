#include <vector>
#include <cstdlib>
#include <cmath>

struct vec2D 
{

	float x;
	float y;

};

struct BoundingBox 
{

	float x;
	float y;
	float width;
	float height;

	bool isCollided( BoundingBox a, BoundingBox b ) 
	{

		if( a.x < b.x + b.width &&
			a.x + a.width > b.x &&
			a.y < b.y + b.height &&
			a.y + a.height > b.y )
		{

			return 1;
			
		}else
		{

			return 0;

		}

	}

};
