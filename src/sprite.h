#ifndef SPRITE_H
#define SPRITE_H

#include <cstdint>

struct Sprite
{
    float x, y;
    std::size_t texture_index;
};

#endif