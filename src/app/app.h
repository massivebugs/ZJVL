#ifndef ZJVL_CORE_APP_H
#define ZJVL_CORE_APP_H

#include "all.h"
#include "framework/window.h"
#include "framework/timer.h"
#include "core/render/renderer.h"
#include "core/scene/scene.h"
#include "core/event/observer.h"
#include "core/event/event.h"

namespace ZJVL
{
	class App : public Core::Observer
	{
	public:
		App(const char *app_name, int win_w, int win_h);
		int run();
		Core::Scene current_scene;
		void on_notify(Core::Event& e) override;
	private:
		const char *m_app_name;
		bool m_running;
		std::uint32_t m_dt;
		std::uint32_t m_fps;

		Framework::Window m_window;
		Core::Renderer m_renderer;

		int execute();

		bool init();

		void update();

		void render();

		void cleanup();
	};
}

#endif