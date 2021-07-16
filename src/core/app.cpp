#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include "app.h"

namespace ZJVL
{

	App::App(const char *app_name, int win_w, int win_h) : m_window(app_name, win_w, win_h), m_renderer(win_w, win_h)
	{
		m_app_name = app_name;
		m_running = true;
	}

	int App::run()
	{
		return on_execute();
	}

	int App::on_execute()
	{
		if (on_init() == false)
		{
			return -1;
		}

		// Loop over and display the splash images
		for (Splash splash_image : current_scene.splash_images)
		{
			m_window.draw_splash(splash_image);
		};

		// Setup game here
		SDL_Event event;
		int rendered_frames = 0;
		Timer fps_timer;

		while (m_running)
		{
			if (fps_timer.get_duration() >= 1000)
			{
				std::cout << "FPS: " << rendered_frames << std::endl;
				rendered_frames = 0;
				fps_timer.reset();
			}

			while (SDL_PollEvent(&event))
			{
				on_event(event);
			};

			on_update();
			on_render();
			rendered_frames++;
		}

		on_cleanup();
		return 0;
	}

	bool App::on_init()
	{
		m_renderer.init();
		return m_window.init();
	}

	void App::on_event(const SDL_Event &event)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_KP_ENTER:
				break;
			case SDLK_ESCAPE:
				break;
			case SDLK_w:
				current_scene.player.x += cos(current_scene.player.angle) * 0.1;
				current_scene.player.y += sin(current_scene.player.angle) * 0.1;
				break;
			case SDLK_a:
				current_scene.player.y += 0.1;
				break;
			case SDLK_s:
				current_scene.player.x -= cos(current_scene.player.angle) * 0.1;
				current_scene.player.y -= sin(current_scene.player.angle) * 0.1;
				break;
			case SDLK_d:
				current_scene.player.x -= 0.1;
				break;
			}
		}

		// Switch through and call event handlers here
	}

	void App::on_update()
	{
		m_window.get_mouse();
		current_scene.player.angle += m_window.mouse_x * M_PI / 360;
	}

	void App::on_render()
	{
		// TODO: referencing
		m_renderer.set_scene(current_scene);
		m_window.draw(m_renderer.render());
	}

	void App::on_cleanup()
	{
		m_renderer.cleanup();
		m_window.cleanup();
	}
}