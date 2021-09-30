#include "all.h"
#include "vec2.h"
#include <SDL2/SDL.h>

namespace ZJVL
{
    Vec2::Vec2() : x(0.f), y(0.f){};
    Vec2::Vec2(float x, float y) : x(x), y(y), point{(int)x, (int)y} {};
    Vec2::Vec2(SDL_Point point) : x(point.x), y(point.y), point(point){};

    Vec2 Vec2::normalize() const
    {
        return Vec2(x, y) / magnitude();
    }

    float Vec2::dot(const Vec2 &v) const
    {
        // std::atan2(v.y, v.x) - std::atan2(y, x) gets the angle between,
        // but atan2() is computationally expensive;
        return x * v.x + y * v.y; // and acos(dot()) to get angle
    }

    Vec2 Vec2::rotate(const float &angle) const
    {
        float sin = std::sin(angle);
        float cos = std::cos(angle);
        return Vec2(x * cos - y * sin, x * sin + y * cos);
    }

    float Vec2::magnitude() const
    {
        return std::sqrt(x * x + y * y);
    }

    float Vec2::magnitude_sq() const
    {
        return (x * x + y * y);
    }

    Vec2 Vec2::operator+(const Vec2 &v) const
    {
        return Vec2(x + v.x, y + v.y);
    }

    Vec2 Vec2::operator-(const Vec2 &v) const
    {
        return Vec2(x - v.x, y - v.y);
    }

    Vec2 Vec2::operator*(const float &val) const
    {
        return Vec2(x * val, y * val);
    }

    Vec2 Vec2::operator*(const Vec2 &v) const
    {
        return Vec2(x * v.x, y * v.y);
    }

    Vec2 Vec2::operator/(const float &val) const
    {
        return Vec2(x / val, y / val);
    }

    Vec2 Vec2::operator/(const Vec2 &v) const
    {
        return Vec2(x / v.x, y / v.y);
    }

    Vec2 &Vec2::operator+=(const Vec2 &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vec2 &Vec2::operator-=(const Vec2 &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
}