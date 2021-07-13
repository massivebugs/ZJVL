#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>
#include "utils/utils.h"
#include "textures.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace ZJVL
{

    Texture::Texture(const char* path) : img_w(0), img_h(0), count(0), size(0), img()
    {
        int tex_w, tex_h;

        SDL_Surface* texture_data = nullptr;
        SDL_Surface* formatted_texture_data = nullptr;
        texture_data = IMG_Load(path);

        if (texture_data == nullptr) {
            std::cout << "Failed to load texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
            return;
        }

        // Flags are unused
        formatted_texture_data = SDL_ConvertSurfaceFormat(texture_data, SDL_PIXELFORMAT_ABGR8888, 0);
        SDL_FreeSurface(texture_data);

        if (formatted_texture_data == nullptr) {
            std::cout << "Failed to format texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
            return;
        }

        tex_w = texture_data->w;
        tex_h = texture_data->h;

        img = std::vector<std::uint32_t>(tex_h * tex_w);

        // Textures are squares
        count = tex_w / tex_h;

        // Get width of each texture tile
        size = tex_w / count;

        img_h = tex_h;

        img_w = tex_w;

        uint8_t *pixels = static_cast<uint8_t *>(formatted_texture_data->pixels);
        // Load the texture into stack memory and close file
        for (int j = 0; j < tex_h; j++)
        {
            for (int i = 0; i < tex_w; i++)
            {
                std::uint32_t texture_pixel = pack_color(
                    pixels[(i + j * tex_w) * 4],
                    pixels[(i + j * tex_w) * 4 + 1],
                    pixels[(i + j * tex_w) * 4 + 2],
                    pixels[(i + j * tex_w) * 4 + 3]);

                img[i + j * tex_w] = texture_pixel;
            }
        }

        SDL_FreeSurface(formatted_texture_data);
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
}