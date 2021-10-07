#ifndef ZJVL_SCENE_CAMERA_H
#define ZJVL_SCENE_CAMERA_H

#include "all.h"
#include <SDL2/SDL.h>
#include "game_object.h"

namespace ZJVL
{
	class Actor;

	class Camera : public GameObject
	{
	public:
		bool create(const Scene &scene) override;
		void update(const Scene &scene, std::uint32_t dt) override;
		void render(const Scene &scene, SDL_Renderer *renderer) override;
		void destroy() override;
		void on_notify(Event &e) override;

		void set_context(const std::shared_ptr<Actor> &actor = nullptr);

	private:
		bool m_detached;
		std::weak_ptr<Actor> context;
	};
}
#endif