#ifndef ZJVL_SPLASH_H
#define ZJVL_SPLASH_H

#include <cstdint>

namespace Engine
{
	struct Splash
	{
		const char *img_path;
		uint32_t display_ms;
	};
}

#endif