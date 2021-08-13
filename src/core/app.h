#ifndef ZJVL_CORE_APP_H
#define ZJVL_CORE_APP_H

#include "all.h"
#include "core/timer.h"
#include "scene/scene.h"
#include "event/observer.h"
#include "event/event.h"
#include "asset/asset_cache.h"
#include "core/input.h"
#include "scene/scene_manager.h"

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
			// Scene::Scene current_scene;
			// void on_notify(Event &e) override;
			SDL_Renderer *m_renderer;
			Input m_input;

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