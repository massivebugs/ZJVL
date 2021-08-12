#ifndef ZJVL_CORE_APP_H
#define ZJVL_CORE_APP_H

#include "all.h"
#include "core/timer.h"
#include "scene/scene.h"
#include "event/observer.h"
#include "event/event.h"
#include "core/asset_cache.h"
#include "core/input.h"
#include "scene/scene_manager.h"

namespace ZJVL
{
	class App : public Core::Subject
	{
	public:
		static App *instance();
		int run();
		Core::SceneManager scene_manager;

		Core::AssetCache asset_cache;
		// Core::Scene current_scene;
		// void on_notify(Core::Event &e) override;
		SDL_Renderer *m_renderer;
		Core::Input m_input;

	private:
		App();
		App(const char *app_name, int win_w, int win_h);
		const char *m_app_name;
		int m_win_w, m_win_h;
		bool m_running;
		std::uint32_t m_dt;
		std::uint32_t m_fps;

		// Core::Window m_window;
		// Core::Renderer m_renderer;

		SDL_Window *m_window;
		SDL_Event m_event;

		int execute();

		bool init();

		void update();

		void render();

		void cleanup();
	};
}

#endif