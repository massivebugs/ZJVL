#ifndef ZJVL_CORE_IMAGE_H
#define ZJVL_CORE_IMAGE_H

#include "all.h"
#include "asset.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace ZJVL
{
	namespace Core
	{
		class Image : public Asset
		{
		public:
			Image(std::string path)
			{
				std::cout << "LOADING IMAGE" << std::endl;
				SDL_Surface *temp = nullptr;

				temp = IMG_Load(path.c_str());

				if (temp == nullptr)
				{
					std::cout << "Failed to load image data . SDL_ERROR: " << SDL_GetError() << std::endl;
					return;
				}

				data = SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_ABGR8888, 0);
				SDL_FreeSurface(temp);

				if (data == nullptr)
					std::cout << "Failed to format image data . SDL_ERROR: " << SDL_GetError() << std::endl;
			}

			~Image()
			{
				std::cout << "REMOVING IMAGE" << std::endl;
				SDL_FreeSurface(data);
			}

			SDL_Surface *data = nullptr;
		};
	}
}

#endif