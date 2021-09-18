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
		GameObject() : w(0), h(0){};
		GameObject(std::size_t w, std::size_t h, Vec2 pos) : pos(pos), w(w), h(h){};

	public:
		virtual ~GameObject() = default;

		virtual bool create(const Scene &scene) = 0;
		virtual void update(std::uint32_t dt) = 0;
		virtual void render(SDL_Renderer *renderer) = 0;
		virtual void destroy() = 0;

		Vec2 pos;
		std::size_t w, h;
	};
}

#endif