#ifndef ZJVL_CORE_APP_H
#define ZJVL_CORE_APP_H

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
		int m_framecount;

		Framework::Window m_window;
		Core::Renderer m_renderer;

		int on_execute();

		bool on_init();

		void on_event();

		void on_update();

		void on_render();

		void on_cleanup();

		// Subject index
		std::size_t m_window_subject;
	};
}

#endif