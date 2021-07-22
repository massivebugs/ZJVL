#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#include <memory>
#include "app.h"
#include "core/scene/scene.h"
#include "core/render/framebuffer.h"
#include "core/event/event.h"
#include "core/event/key_event.h"

namespace ZJVL
{
	App::App(const char *app_name, int win_w, int win_h) : m_window(app_name, win_w, win_h), m_renderer(win_w, win_h)
	{
		m_app_name = app_name;
		m_framecount = 0;
		m_running = true;
	}

	// Begins game loop execution
	int App::run()
	{
		return on_execute();
	}

	// This is the main execution loop,
	// where all of the game loop functionalities
	// are tied together.
	int App::on_execute()
	{
		// Handle initialization failures
		if (on_init() == false)
		{
			return -1;
		}

		// Set up the game here
		Framework::Timer fps_timer;
		SDL_Event event;

		std::vector<Core::Entity> entities = std::vector<Core::Entity>{{3.523, 3.812, NULL, NULL, 2}, {1.834, 8.765, NULL, NULL, 0}, {5.323, 5.365, NULL, NULL, 1}, {4.123, 10.265, NULL, NULL, 2}};
		Core::Entity player{3.456, 2.345, 1.523, M_PI / 3.};
		Core::Map map;
		Core::Scene scene{map, player, entities};
		scene.load_splash(Core::Splash{"assets/splash_zjvl.png", 3000});
		current_scene = scene;

		while (m_running)
		{
			// if (!current_scene.is_activated())
			// {
			// 	// Loop over and display the splash images
			// 	for (Core::Splash &splash_image : current_scene.splash_images)
			// 	{
			// 		m_window.flash_image(splash_image.img_path, splash_image.display_ms);
			// 	};
			// }

			// An example of how the Timer class can be used as an FPS counter.
			// Use .reset() and .get_duration()
			// to retrieve how many miliseconds has passed since the last .reset()
			if (fps_timer.get_duration() >= 1000)
			{
				std::cout << "FPS: " << m_framecount << std::endl;
				m_framecount = 0;
				fps_timer.reset();
			}

			while (SDL_PollEvent(&event))
			{
				on_event(event);
			};

			on_update();
			on_render();
			m_framecount++;
		}

		on_cleanup();
		return 0;
	}

	void App::on_event(SDL_Event &event)
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
		// while (m_window.poll_event(e))
		// {
		// 	switch (e->get_type())
		// 	{
		// 	case Core::EventType::QUIT:
		// 		m_running = false;
		// 		break;
		// 	case Core::EventType::KEYDOWN:
		// 		switch (std::static_pointer_cast<Core::KeyDownEvent>(e)->get_key())
		// 		{
		// 		case Core::Key::ENTER:
		// 			break;
		// 		case Core::Key::ESC:
		// 			break;
		// 		case Core::Key::W:
		// 			current_scene.player.x += cos(current_scene.player.angle) * 0.1;
		// 			current_scene.player.y += sin(current_scene.player.angle) * 0.1;
		// 			break;
		// 		case Core::Key::A:
		// 			current_scene.player.y += 0.1;
		// 			break;
		// 		case Core::Key::S:
		// 			current_scene.player.x -= cos(current_scene.player.angle) * 0.1;
		// 			current_scene.player.y -= sin(current_scene.player.angle) * 0.1;
		// 			break;
		// 		case Core::Key::D:
		// 			current_scene.player.x -= 0.1;
		// 			break;
		// 		}
		// 		break;
		// 	}
		// }
	}

	// This is where any post processing gameplay updates may happen.
	// Note that this is called after the event handlers have been called,
	// and is the final step before updates to do any kind of processing.
	void App::on_update()
	{
		m_window.get_mouse();
		current_scene.player.angle += m_window.mouse_x * M_PI / 360;
	}

	bool App::on_init()
	{
		m_renderer.init();
		return m_window.init();
	}

	void App::on_render()
	{
		m_renderer.set_scene(current_scene);
		Core::FrameBuffer *framebuffer = m_renderer.render();
		m_window.draw(static_cast<void *>(framebuffer->img.data()), framebuffer->w * 4);
	}

	void App::on_cleanup()
	{
		m_renderer.cleanup();
		m_window.cleanup();
	}
}