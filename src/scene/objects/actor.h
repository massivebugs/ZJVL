#ifndef ZJVL_SCENE_ACTOR_H
#define ZJVL_SCENE_ACTOR_H

#include "all.h"
#include <SDL2/SDL.h>
#include "core/vec2.h"
#include "scene/game_object.h"
#include "scene/scene.h"

namespace ZJVL
{
	class Actor : public GameObject
	{
	protected:
		Actor(const std::string &name, std::size_t texture_index)
		    : name(name),
		      texture_index(texture_index){
			      angle = 0;
			      fov = M_PI / 3.f;
		      };

	public:
		virtual ~Actor() = default;
		virtual bool create(const Scene &scene) = 0;
		virtual void update(std::uint32_t dt) = 0;
		virtual void render(SDL_Renderer *renderer) = 0;
		virtual void destroy() = 0;
		virtual void on_notify(Event &e) = 0;

		std::string name;
		float angle;
		float fov;

		std::size_t texture_index; // TODO: Change to Texture or Animation
	};
}

#endif