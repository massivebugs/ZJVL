#ifndef ZJVL_CORE_TEXTURE_H
#define ZJVL_CORE_TEXTURE_H

#include "all.h"
#include "asset.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace ZJVL
{
	namespace Asset
	{
		class TextureX : public Asset
		{
		public:
			TextureX(int w, int h, SDL_Renderer *renderer)
			{
				std::cout << "LOADING TEX" << std::endl;
				data = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, w, h);
			}

			TextureX(std::string path, SDL_Renderer *renderer)
			{
				std::cout << "LOADING TEX" << std::endl;
				SDL_Surface *temp = nullptr;

				temp = IMG_Load(path.c_str());

				if (temp == nullptr)
				{
					std::cout << "Failed to load texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
					return;
				}

				data = SDL_CreateTextureFromSurface(renderer, temp);

				if (data == nullptr)
					std::cout << "Failed to load texture data . SDL_ERROR: " << SDL_GetError() << std::endl;

				SDL_FreeSurface(temp);
			}

			~TextureX()
			{
				std::cout << "DESTROYING TEX" << std::endl;
				SDL_DestroyTexture(data);
			}

			SDL_Texture *data = nullptr;
		};
	}
}

#endif