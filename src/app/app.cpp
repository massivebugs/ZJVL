#include <iostream>
#include <math.h>
#include <memory>
#include "app.h"
#include "core/scene/scene.h"
#include "core/render/framebuffer.h"

namespace ZJVL
{
	App::App(const char *app_name, int win_w, int win_h)
	    : m_app_name(app_name),
	      m_dt(0),
	      m_fps(0),
	      m_running(true),
	      m_window(app_name, win_w, win_h),
	      m_renderer(win_w, win_h)
	{
	}

	// Begins game loop execution
	int App::run()
	{
		return execute();
	}

	// This is the main execution loop,
	// where all of the game loop functionalities
	// are tied together.
	int App::execute()
	{
		// Handle initialization failures
		if (init() == false)
		{
			return -1;
		}

		// Set up the game here
		std::vector<Core::Entity> entities = std::vector<Core::Entity>{{3.523, 3.812, 2}, {1.834, 8.765, 0}, {5.323, 5.365, 1}, {4.123, 10.265, 2}};
		Core::Entity player{3.456, 2.345, 1.523, M_PI / 3.f};
		Core::Map map;
		Core::Scene scene{map, player, entities};
		scene.load_splash(Core::Splash{"assets/splash_zjvl.png", 3000});
		current_scene = scene;

		Framework::Timer timer;
		int framecount = 0;
		std::uint32_t dt_start_time = timer.get_time();
		std::uint32_t dt_end_time = 0;
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

			update();
			render();

			framecount++;
			if(timer.get_duration() >= 1000) {
				m_fps = framecount;
				std::cout << "FPS: " << m_fps << std::endl;
				framecount = 0;
				timer.reset_duration();
			}

			// Calculate Delta Time
			dt_end_time = timer.get_time();
			m_dt = dt_end_time - dt_start_time;
			dt_start_time = dt_end_time;
		}

		cleanup();
		return 0;
	}

	bool App::init()
	{
		m_renderer.init();
		m_window_subject = m_window.add_observer(this);
		return m_window.init();
	}

	// This is where any post processing gameplay updates may happen.
	// Note that this is called after the event handlers have been called,
	// and is the final step before updates to do any kind of processing.
	void App::update()
	{
		m_window.poll_events();
		// current_scene.player.angle += m_window.mouse_x * M_PI / 360;
	}

	void App::render()
	{
		m_renderer.set_scene(current_scene);
		Core::FrameBuffer *framebuffer = m_renderer.render();
		m_window.draw(static_cast<void *>(framebuffer->img.data()), framebuffer->w * 4);
	}

	void App::cleanup()
	{
		m_renderer.cleanup();
		m_window.remove_observer(m_window_subject);
		m_window.cleanup();
	}

	// This is where all events are handled at the application level.
	// For Scene, Entity specific events, use their own respective member functions.
	void App::on_notify(Core::Event &e)
	{
		switch (e.get_type())
		{
		case Core::EventType::WINDOW_QUIT:
			m_running = false;
			break;
		case Core::EventType::KEYDOWN:
			switch (static_cast<Core::KeyDownEvent &>(e).get_key())
			{
			case Core::Key::ENTER:
				break;
			case Core::Key::ESC:
				break;
			case Core::Key::W:
				// current_scene.player.x += cos(current_scene.player.angle) * 0.1;
				// current_scene.player.y += sin(current_scene.player.angle) * 0.1;
				break;
			case Core::Key::A:
				// current_scene.player.y += 0.1;
				break;
			case Core::Key::S:
				// current_scene.player.x -= cos(current_scene.player.angle) * 0.1;
				// current_scene.player.y -= sin(current_scene.player.angle) * 0.1;
				break;
			case Core::Key::D:
				// current_scene.player.x -= 0.1;
				break;
			}
			break;
		}
	}
}