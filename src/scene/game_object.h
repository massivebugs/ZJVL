#ifndef ZJVL_SCENE_GAMEOBJECT_H
#define ZJVL_SCENE_GAMEOBJECT_H

#include "all.h"
#include <SDL2/SDL.h>
#include "core/vec2.h"
#include "event/observer.h"
#include "scene.h"

namespace ZJVL
{
	class GameObject
	{
	protected:
		GameObject() = default;

	public:
		virtual ~GameObject() = default;
		virtual bool create(const Scene &scene) = 0;
		virtual void update(std::uint32_t dt) = 0;
		virtual void render(SDL_Renderer *renderer) = 0;
		virtual void destroy() = 0;
	};
}

#endif