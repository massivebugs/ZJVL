#ifndef ZJVL_SCENE_ACTOR_H
#define ZJVL_SCENE_ACTOR_H

#include "all.h"
#include <SDL2/SDL.h>
#include "scene/game_object.h"
#include "core/vec2.h"
#include "scene/scene.h"
#include "event/observer.h"
#include "asset/sprite_sheet.h"

namespace ZJVL
{
	class Actor : public GameObject, public Observer
	{
	public:
		virtual ~Actor() = default;
		virtual bool create(const Scene &scene) = 0;
		virtual void update(const Scene &scene, std::uint32_t dt) = 0;
		virtual void render(SDL_Renderer *renderer) = 0;
		virtual void destroy() = 0;
		virtual void on_notify(Event &e) = 0;

		std::string name;
		float angle;
		float fov;
		std::size_t w, h;
		SpriteSheet texture;

	protected:
		Actor(const Vec2 &pos, const std::string &texture_path)
			: texture(texture_path),
			  GameObject(pos)
		{
			angle = 0;
			fov = M_PI / 3.f;
		};
	};
}

#endif