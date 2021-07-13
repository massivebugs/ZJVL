#ifndef ZJVL_APP_H
#define ZJVL_APP_H

#include "window.h"
#include "renderer/renderer.h"
#include "scene/scene.h"

namespace ZJVL
{
	class App
	{
	public:
		App(const char *app_name, int win_w, int win_h);
		int run();
		Scene current_scene;

	private:
		const char *m_app_name;
		bool m_running;

		Window m_window;
		Renderer m_renderer;

	private:
		int on_execute();

		bool on_init();

		void on_event(const SDL_Event &event);

		void on_update();

		void on_render();

		void on_cleanup();
	};
}

#endif