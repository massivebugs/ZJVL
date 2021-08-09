#ifndef ZJVL_CORE_APP_H
#define ZJVL_CORE_APP_H

#include "all.h"
#include "core/core/window.h"
#include "core/core/timer.h"
#include "core/render/renderer.h"
#include "core/scene/scene.h"
#include "core/event/observer.h"
#include "core/event/event.h"
#include "core/core/asset_cache.h"

namespace ZJVL
{
	class App : public Core::Observer
	{
	public:
		// static App *instance();
		App();
		App(const char *app_name, int win_w, int win_h);
		int run();
		Core::Scene current_scene;
		void on_notify(Core::Event &e) override;
		SDL_Renderer *renderer;

	private:
		const char *m_app_name;
		bool m_running;
		std::uint32_t m_dt;
		std::uint32_t m_fps;

		Core::Window m_window;
		Core::Renderer m_renderer;

		Core::AssetCache m_asset_cache;

		int execute();

		bool init();

		void update();

		void render();

		void cleanup();
	};
}

#endif