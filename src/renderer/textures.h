#ifndef ZJVL_TEXTURES_H
#define ZJVL_TEXTURES_H

// https://www.learncpp.com/cpp-tutorial/returning-values-by-value-reference-and-address/
// https://stackoverflow.com/questions/8610350/implications-of-using-an-ampersand-before-a-function-name-in-c

#include <cstdint>
#include <vector>
#include <string>

namespace Engine
{
    class Texture
    {
    public:
        Texture(const char *path);
        std::size_t img_w, img_h; // image dimensions
        std::size_t count, size;  // textures count and size
        std::vector<uint32_t> img;

        std::uint32_t &get(const std::size_t row, const std::size_t col, const std::size_t index);
        std::vector<uint32_t> get_scaled_column(const std::size_t index, const std::size_t col, const std::size_t column_height);
    };
}

#endif