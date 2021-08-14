#ifndef ZJVL_CORE_APP_H
#define ZJVL_CORE_APP_H

#include "all.h"
#include "event/subject.h"
#include "asset/asset_cache.h"
#include "core/input_system.h"
#include "scene/scene_manager.h"
#include "core/timer.h"

namespace ZJVL
{
	namespace Core
	{
		class App : public Event::Subject
		{
		public:
			static App *instance();
			bool init();
			int run();

			Scene::SceneManager scene_manager;
			Asset::AssetCache asset_cache;
			InputSystem input_system;
			SDL_Renderer *renderer;

			const char *name;
			int window_w, window_h;

		private:
			App();

			bool m_running;
			std::uint32_t m_dt;
			std::uint32_t m_fps;

			SDL_Window *m_window;
			SDL_Event m_event;

			void update();

			void render();

			void cleanup();
		};
	}
}

#endif