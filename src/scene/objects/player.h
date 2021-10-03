#ifndef ZJVL_SCENE_SCENE_PLAYER_H
#define ZJVL_SCENE_SCENE_PLAYER_H

#include "all.h"
#include "scene/actor.h"

namespace ZJVL
{
	class Player : public Actor
	{
	public:
		Player(const Vec2 &pos, const std::string &texture_path);

		bool create(const Scene &scene) override;
		void update(const Scene &scene, std::uint32_t dt) override;
		void render(const Scene &scene, SDL_Renderer *renderer) override;
		void destroy() override;
		virtual void on_notify(Event &e) override;
	};
}

#endif