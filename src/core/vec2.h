#ifndef ZJVL_UTIL_VEC2_H
#define ZJVL_UTIL_VEC2_H

#include "all.h"
#include <SDL2/SDL.h>

namespace ZJVL
{
	struct Vec2
	{
		Vec2() : x(0.f), y(0.f){};
		Vec2(float x, float y) : x(x), y(y), point{(int)x, (int)y} {};
		Vec2(SDL_Point point) : x(point.x), y(point.y), point(point){};

		Vec2 normalize() const
		{
			return Vec2(x, y) / magnitude();
		}

		float dot(const Vec2 &v) const
		{
			// std::atan2(v.y, v.x) - std::atan2(y, x) gets the angle between,
			// but atan2() is computationally expensive;
			return x * v.x + y * v.y; // and acos(dot()) to get angle
		}

		Vec2 rotate(const float &angle) const
		{
			float sin = std::sin(angle);
			float cos = std::cos(angle);
			return Vec2(x * cos - y * sin, x * sin + y * cos);
		}

		float magnitude() const
		{
			return std::sqrt(x * x + y * y);
		}

		float magnitude_sq() const
		{
			return (x * x + y * y);
		}

		Vec2 operator+(const Vec2 &v) const
		{
			return Vec2(x + v.x, y + v.y);
		}

		Vec2 operator-(const Vec2 &v) const
		{
			return Vec2(x - v.x, y - v.y);
		}

		Vec2 operator*(const float &val) const
		{
			return Vec2(x * val, y * val);
		}

		Vec2 operator*(const Vec2 &v) const
		{
			return Vec2(x * v.x, y * v.y);
		}

		Vec2 operator/(const float &val) const
		{
			return Vec2(x / val, y / val);
		}

		Vec2 operator/(const Vec2 &v) const
		{
			return Vec2(x / v.x, y / v.y);
		}

		Vec2 &operator+=(const Vec2 &v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		Vec2 &operator-=(const Vec2 &v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		SDL_Point point;
		float x;
		float y;
	};
}

#endif