#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "utils.h"

uint8_t *Utils::load_image(const char *path, int *img_w, int *img_h)
{
        SDL_Surface* texture_data = nullptr;
        SDL_Surface* formatted_texture_data = nullptr;
        texture_data = IMG_Load(path);

        if (texture_data == nullptr) {
            std::cout << "Failed to load texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
            return nullptr;
        }

        // Flags are unused
        formatted_texture_data = SDL_ConvertSurfaceFormat(texture_data, SDL_PIXELFORMAT_ABGR8888, 0);
        SDL_FreeSurface(texture_data);

        if (formatted_texture_data == nullptr) {
            std::cout << "Failed to format texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
            return nullptr;
        }

        *img_w = texture_data->w;
        *img_h = texture_data->h;
        return static_cast<uint8_t *>(formatted_texture_data->pixels);
}