#ifndef ZJVL_CORE_SPLASH_H
#define ZJVL_CORE_SPLASH_H
#include "all.h"

namespace ZJVL
{
	namespace Core
	{
		struct Splash
		{
			const char *img_path;
			std::uint32_t display_ms;
		};

	}
}

#endif