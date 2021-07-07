#ifndef TEXTURES_H
#define TEXTURES_H

// https://www.learncpp.com/cpp-tutorial/returning-values-by-value-reference-and-address/
// https://stackoverflow.com/questions/8610350/implications-of-using-an-ampersand-before-a-function-name-in-c

#include <cstdint>
#include <vector>

struct Texture
{
    std::size_t img_w, img_h; // image dimensions
    std::size_t count, size;  // textures count and size
    std::vector<uint32_t> img;

    Texture();
    Texture(const std::string filename);
    std::uint32_t &get(const std::size_t row, const std::size_t col, const std::size_t index);
    std::vector<uint32_t> get_scaled_column(const std::size_t index, const std::size_t col, const std::size_t column_height);
};

#endif