#ifndef ZJVL_SCENE_MAP_H
#define ZJVL_SCENE_MAP_H

#include "all.h"

namespace ZJVL
{
    namespace Scene
    {
        struct Map
        {
            Map();

            // Size of map, default is 16 for each
            std::size_t w, h;

            // Retrieve the texture index of the position in the map
            int get(const std::size_t row, const std::size_t col);

            // Check if the position has no elements
            bool is_empty(const std::size_t row, const std::size_t col);
        };
    }
}

#endif