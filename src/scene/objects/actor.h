#ifndef ZJVL_SCENE_ACTOR_H
#define ZJVL_SCENE_ACTOR_H

#include "all.h"
#include <SDL2/SDL.h>
#include "scene/game_object.h"
#include "core/vec2.h"

namespace ZJVL
{
	class Actor : public GameObject
	{
	public:
		Actor(Vec2 vec2);
		virtual ~Actor() = default;

		float angle, fov;
		std::size_t texture_index; // TODO: Change to Texture

		virtual bool create() = 0;
		virtual void update(std::uint32_t dt) = 0;
		virtual void render(SDL_Renderer *renderer) = 0;
		virtual void destroy() = 0;

		virtual void on_notify(Event &e) = 0;

	public:
	};
}

#endif