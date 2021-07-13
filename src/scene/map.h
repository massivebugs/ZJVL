#ifndef ZJVL_MAP_H
#define ZJVL_MAP_H

#include <cstdint>

namespace Engine
{
    struct Map
    {
        // Size of map, default is 16 for each
        std::size_t w, h;

        // We will be defining a constructor
        Map();

        // Retrieve the texture index of the position in the map
        int get(const std::size_t row, const std::size_t col);

        // Check if the position has no elements
        bool is_empty(const std::size_t row, const std::size_t col);
    };
}

#endif