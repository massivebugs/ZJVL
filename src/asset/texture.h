#ifndef ZJVL_ASSET_TEXTURE_H
#define ZJVL_ASSET_TEXTURE_H

#include "all.h"
#include "asset.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "core/app.h"

namespace ZJVL
{
	namespace Asset
	{
		class Texture : public Asset
		{
		public:
			Texture(int w, int h) : w(w), h(h)
			{
				data = SDL_CreateTexture(Core::App::instance()->renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, w, h);

				if (data == nullptr)
				{
					std::cout << "Failed to load texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
					return;
				}
			}

			Texture(std::string path)
			{
				data = IMG_LoadTexture(Core::App::instance()->renderer, path.c_str());

				if (data == nullptr)
				{
					std::cout << "Failed to load texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
					return;
				}

				SDL_QueryTexture(data, nullptr, nullptr, &w, &h);
			}

			~Texture()
			{
				SDL_DestroyTexture(data);
			}

			void set_blending(SDL_BlendMode blending = SDL_BLENDMODE_BLEND)
			{
				SDL_SetTextureBlendMode(data, blending);
			};

			void set_alpha(std::uint8_t a)
			{
				SDL_SetTextureAlphaMod(data, a);
			}

			void lock()
			{
				// TODO: Change
				void *temp_pixels;
				// TODO: Error handling
				SDL_LockTexture(data, NULL, &temp_pixels, &pitch);
				pixels = (std::uint32_t *)temp_pixels;
			}

			void unlock()
			{
				SDL_UnlockTexture(data);
				pixels = nullptr;
				pitch = 0;
			}

			SDL_Texture *data = nullptr;
			int w, h;

			// Probably unused
			std::uint32_t *pixels;
			int pitch;
		};
	}
}

#endif