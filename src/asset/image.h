#ifndef ZJVL_ASSET_IMAGE_H
#define ZJVL_ASSET_IMAGE_H

#include "all.h"
#include "asset.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace ZJVL
{
	namespace Asset
	{
		class Image : public Asset
		{
		public:
			Image(std::string path)
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
				data = std::vector<std::uint32_t>(pixels, pixels + w * h);

				SDL_FreeSurface(formatted_surface);
			}

			~Image(){}

			std::vector<std::uint32_t> data;
			std::size_t w, h;
		};
	}
}

#endif