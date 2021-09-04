#ifndef ZJVL_SCENE_USER_H
#define ZJVL_SCENE_USER_H

#include "all.h"
#include <SDL2/SDL.h>
#include "actor.h"
#include "core/vec2.h"


namespace ZJVL
{
	class User : public Actor
	{
		User(const std::string &name, std::size_t texture_index);
		virtual bool create(const Scene& scene) override;
		virtual void update(std::uint32_t dt) override;
		virtual void render(SDL_Renderer *renderer) override;
		virtual void destroy() override;
		virtual void on_notify(Event &e) override;
	};
	
}

#endif