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

			int run();

			Scene::SceneManager scene_manager;
			Asset::AssetCache asset_cache;
			InputSystem input_system;

			SDL_Renderer *renderer;

		private:
			App();
			App(const char *app_name, int win_w, int win_h);

			const char *m_app_name;
			int m_win_w, m_win_h;
			bool m_running;

			std::uint32_t m_dt;
			std::uint32_t m_fps;

			SDL_Window *m_window;
			SDL_Event m_event;

			int execute();

			bool init();

			void update();

			void render();

			void cleanup();
		};
	}
}

#endif