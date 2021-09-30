#ifndef ZJVL_ASSET_TEXTURE_H
#define ZJVL_ASSET_TEXTURE_H

#include "all.h"
#include "asset.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace ZJVL
{
	class Texture : public Asset
	{
	public:
		Texture(int w, int h);
		Texture(const std::string &path);
		~Texture();

		void set_blending(SDL_BlendMode blending = SDL_BLENDMODE_BLEND);

		void set_alpha(std::uint8_t a);

		void lock();

		void unlock();

		SDL_Texture *data = nullptr;
		int w, h;

		// Probably unused
		std::uint32_t *pixels;
		int pitch;
	};
}

#endif