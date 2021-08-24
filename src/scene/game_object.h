#ifndef ZJVL_SCENE_GAMEOBJECT_H
#define ZJVL_SCENE_GAMEOBJECT_H

#include "all.h"
#include <SDL2/SDL.h>
#include "event/observer.h"
#include "core/vec2.h"

namespace ZJVL
{
	class GameObject : public Observer
	{
	public:
		GameObject(Vec2 vec2, std::size_t w, std::size_t h)
		    : vec2(vec2),
		      w(w),
		      h(h){};
		virtual ~GameObject() = default;

		Vec2 vec2;
		std::size_t w, h;

		virtual bool create() = 0;
		virtual void update(std::uint32_t dt) = 0;
		virtual void render(SDL_Renderer *renderer) = 0;
		virtual void destroy() = 0;

		virtual void on_notify(Event &e) = 0;
	};
}

#endif