#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "utils.h"

namespace ZJVL
{
    namespace Framework
    {
        void Utils::load_image(const char *path, std::vector<std::uint32_t> *img, std::size_t *img_w, std::size_t *img_h)
        {
            SDL_Surface *texture_data = nullptr;
            SDL_Surface *formatted_texture_data = nullptr;
            texture_data = IMG_Load(path);

            if (texture_data == nullptr)
            {
                std::cout << "Failed to load texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
                return;
            }

            // Flags are unused
            formatted_texture_data = SDL_ConvertSurfaceFormat(texture_data, SDL_PIXELFORMAT_ABGR8888, 0);
            SDL_FreeSurface(texture_data);

            if (formatted_texture_data == nullptr)
            {
                std::cout << "Failed to format texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
                return;
            }

            *img_w = texture_data->w;
            *img_h = texture_data->h;

            uint32_t *pixels = static_cast<uint32_t *>(formatted_texture_data->pixels);
            *img = std::vector<std::uint32_t>(pixels, pixels + (*img_w) * (*img_h));

            SDL_FreeSurface(formatted_texture_data);
        }

    }
}