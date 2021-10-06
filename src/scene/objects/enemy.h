#ifndef ZJVL_SCENE_ENEMY_H
#define ZJVL_SCENE_ENEMY_H

#include "all.h"
#include <SDL2/SDL.h>
#include "scene/actor.h"
#include "util/vec2.h"

namespace ZJVL
{
	class Enemy : public Actor
	{
	public:
		Enemy(const Vec2 &pos, const std::string &texture_path);
		virtual bool create(const Scene &scene) override;
		virtual void update(const Scene &scene, std::uint32_t dt) override;
		virtual void render(const Scene &scene, SDL_Renderer *renderer) override;
		virtual void destroy() override;
		virtual void on_notify(Event &e) override;
	};

}

#endif