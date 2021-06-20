#ifndef SPRITE_H
#define SPRITE_H

#include <cstdint>

struct Sprite
{
    float x, y;
    std::size_t texture_index;
    float player_dist;
    // const functions - https://stackoverflow.com/questions/3141087/what-is-meant-with-const-at-end-of-function-declaration
    bool operator < (const Sprite& s) const; // Operator overloading using member functions
};

#endif