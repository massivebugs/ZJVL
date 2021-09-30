#include "all.h"
#include "image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace ZJVL
{
    Image::Image(std::string path)
    {
        SDL_Surface *surface = nullptr;
        SDL_Surface *formatted_surface = nullptr;

        surface = IMG_Load(path.c_str());

        if (surface == nullptr)
        {
            std::cout << "Failed to load image data . SDL_ERROR: " << SDL_GetError() << std::endl;
            return;
        }

        formatted_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, 0);
        SDL_FreeSurface(surface);

        if (formatted_surface == nullptr)
        {
            std::cout << "Failed to format image data . SDL_ERROR: " << SDL_GetError() << std::endl;
            return;
        }

        w = formatted_surface->w;
        h = formatted_surface->h;
        uint32_t *pixels = static_cast<uint32_t *>(formatted_surface->pixels);
        buffer = std::vector<std::uint32_t>(pixels, pixels + w * h);

        SDL_FreeSurface(formatted_surface);
    }
}