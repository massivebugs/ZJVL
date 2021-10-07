#ifndef ZJVL_SCENE_GAMEOBJECT_H
#define ZJVL_SCENE_GAMEOBJECT_H

#include "all.h"
#include <SDL2/SDL.h>
#include "util/vec2.h"
#include "event/observer.h"

namespace ZJVL
{
	class Scene;

	class GameObject : public Observer
	{
	protected:
		GameObject(const Vec2 &pos = Vec2());

	public:
		virtual ~GameObject() = default;
		virtual bool create(const Scene &scene) = 0;
		virtual void update(const Scene &scene, std::uint32_t dt) = 0;
		virtual void render(const Scene &scene, SDL_Renderer *renderer) = 0;
		virtual void destroy() = 0;
		virtual void on_notify(Event &e) = 0;

		float get_object_distance(const GameObject &other);

		Vec2 pos;

		std::string name;
	};
}

#endif