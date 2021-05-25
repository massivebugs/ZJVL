#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
#include "utils.h"
#include "textures.h"

Texture::Texture(const std::string filename) : img_w(0), img_h(0), count(0), size(0), img()
{
    int pix_channels, tex_w, tex_h;
    const int pix_length = 4; // RGBA

    unsigned char *texture_data = stbi_load(filename.c_str(), &tex_w, &tex_h, &pix_channels, pix_length);

    if (texture_data == NULL)
        return;

    img = std::vector<std::uint32_t>(tex_h * tex_w);

    // Textures are squares
    count = tex_w / tex_h;

    // Get width of each texture tile
    size = tex_w / count;

    img_h = tex_h;

    img_w = tex_w;

    // Load the texture into stack memory and close file
    for (int j = 0; j < tex_h; j++)
    {
        for (int i = 0; i < tex_w; i++)
        {
            std::uint32_t texture_pixel = pack_color(
                texture_data[(i + j * tex_w) * 4],
                texture_data[(i + j * tex_w) * 4 + 1],
                texture_data[(i + j * tex_w) * 4 + 2],
                texture_data[(i + j * tex_w) * 4 + 3]);

            img[i + j * tex_w] = texture_pixel;
        }
    }

    stbi_image_free(texture_data);
}

std::uint32_t &Texture::get(const std::size_t row, const std::size_t col, const std::size_t index)
{
    assert(row < size && col < size && index < count);
    return img[col + (index * size) + (row * img_w)];
}

std::vector<uint32_t> Texture::get_scaled_column(const std::size_t index, const std::size_t col, const std::size_t column_height)
{
    assert(col < size && index < count);
    std::vector<std::uint32_t> column(column_height);

    for (int curr_column_height = 0; curr_column_height < column_height; curr_column_height++)
    {
        std::size_t row = float(size) / float(column_height) * curr_column_height;
        column[curr_column_height] = get(row, col, index);
    }

    return column;
}