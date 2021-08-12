#ifndef ZJVL_CORE_SPLASH_H
#define ZJVL_CORE_SPLASH_H
#include "all.h"
#include <SDL2/SDL.h>

namespace ZJVL
{
	namespace Scene
	{
		struct Splash
		{
			// SDL_Texture *splash_image;
			const char* img_path;
			std::uint32_t display_ms;
		};

	}
}

#endif