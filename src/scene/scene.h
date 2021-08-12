#ifndef ZJVL_CORE_SCENE_H
#define ZJVL_CORE_SCENE_H
#include "all.h"
#include <SDL2/SDL.h>

namespace ZJVL
{
	namespace Scene
	{
		class Scene
		{
			public:
				virtual ~Scene() = default;

				virtual void load() = 0;
				virtual void unload() = 0;
				virtual void update(std::uint32_t dt) = 0;
				virtual void render(SDL_Renderer *renderer) = 0;
		};
	}
}
#endif