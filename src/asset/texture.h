#ifndef ZJVL_ASSET_TEXTURE_H
#define ZJVL_ASSET_TEXTURE_H

#include "all.h"
#include "asset.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace ZJVL
{
	namespace Asset
	{
		class Texture : public Asset
		{
		public:
			Texture(int w, int h, SDL_Renderer *renderer)
			{
				data = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, w, h);
			}

			Texture(std::string path, SDL_Renderer *renderer)
			{
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

			~Texture()
			{
				SDL_DestroyTexture(data);
			}

			void lock() {
				// TODO: Change
				void* temp_pixels;
				// TODO: Error handling
				SDL_LockTexture(data, NULL, &temp_pixels, &pitch);
				pixels = (std::uint32_t *) temp_pixels;
			}

			void unlock() {
				SDL_UnlockTexture(data);
				pixels = nullptr;
				pitch = 0;
			}

			SDL_Texture *data = nullptr;
			std::uint32_t *pixels;
			int pitch;
		};
	}
}

#endif