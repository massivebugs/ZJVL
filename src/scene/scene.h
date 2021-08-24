#ifndef ZJVL_SCENE_SCENE_H
#define ZJVL_SCENE_SCENE_H

#include "all.h"
#include <SDL2/SDL.h>

namespace ZJVL
{
	class Scene
	{
	public:
		virtual ~Scene() = default;

		// TODO: Add Camera

		virtual void load() = 0;
		virtual void unload() = 0;
		virtual void update(std::uint32_t dt) = 0;
		virtual void render(SDL_Renderer *renderer) = 0;
	};
}
#endif