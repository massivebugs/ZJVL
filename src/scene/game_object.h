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
		GameObject() : w(0), h(0){};
		GameObject(Vec2 pos, std::size_t w, std::size_t h) : pos(pos), w(w), h(h){};
		virtual ~GameObject() = default;

		Vec2 pos;
		std::size_t w, h;

		virtual bool create() = 0;
		virtual void update(std::uint32_t dt) = 0;
		virtual void render(SDL_Renderer *renderer) = 0;
		virtual void destroy() = 0;

		virtual void on_notify(Event &e) = 0;
	};
}

#endif