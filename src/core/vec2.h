#ifndef ZJVL_UTIL_VEC2_H
#define ZJVL_UTIL_VEC2_H

#include "all.h"
#include <SDL2/SDL.h>

namespace ZJVL
{
	class Vec2
	{
	public:
		Vec2() : x(0), y(0){};
		Vec2(float x, float y) : x(x), y(y), point{(int)x, (int)y} {};
		Vec2(SDL_Point point) : x(point.x), y(point.y), point(point){};

		SDL_Point point;
		float x;
		float y;
	};
}

#endif