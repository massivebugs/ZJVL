#ifndef ZJVL_UTIL_VEC2_H
#define ZJVL_UTIL_VEC2_H

#include "all.h"
#include <SDL2/SDL.h>

namespace ZJVL
{
	struct Vec2
	{
		Vec2();
		Vec2(float x, float y);
		Vec2(SDL_Point point);

		Vec2 normalize() const;

		float dot(const Vec2 &v) const;

		Vec2 rotate(const float &angle) const;

		float magnitude() const;

		float magnitude_sq() const;

		Vec2 operator+(const Vec2 &v) const;

		Vec2 operator-(const Vec2 &v) const;

		Vec2 operator*(const float &val) const;

		Vec2 operator*(const Vec2 &v) const;

		Vec2 operator/(const float &val) const;

		Vec2 operator/(const Vec2 &v) const;

		Vec2 &operator+=(const Vec2 &v);

		Vec2 &operator-=(const Vec2 &v);

		SDL_Point point;
		float x;
		float y;
	};
}

#endif