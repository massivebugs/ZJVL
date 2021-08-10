#include "all.h"
#include "app.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "core/scene/scene.h"
// #include "core/render/framebuffer.h"
#include "core/core/image.h"
#include "core/event/subject.h"
#include "core/event/events/window_event.h"
#include "scenes/splash_scene.h"
#include "scenes/game_scene.h"
#include "core/core/texture.h"

namespace ZJVL
{
	App *App::instance()
	{
		static App *instance = new App();
		return instance;
	}

	App::App()
	    : m_app_name("testgame"),
	      m_win_w(1024),
	      m_win_h(512),
	      m_dt(0),
	      m_fps(0),
	      m_running(false),
	      m_window(nullptr),
	      m_renderer(nullptr)
	{
		std::cout << "Creating App instance!!!" << std::endl;
	}

	App::App(const char *app_name, int win_w, int win_h)
	    : m_app_name(app_name),
	      m_win_w(win_w),
	      m_win_h(win_h),
	      m_dt(0),
	      m_fps(0),
	      m_running(false),
	      m_window(nullptr),
	      m_renderer(nullptr)
	{
	}

	// Begins game loop execution
	int App::run()
	{
		if (!m_running)
			m_running = true;
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

		std::shared_ptr<Core::Image> image = asset_cache.get<Core::Image>("assets/splash_zjvl.png");
		std::shared_ptr<Core::Image> image2 = asset_cache.get<Core::Image>("assets/splash_zjvl.png");

		// Set up the game here
		// std::vector<Core::Entity> entities = std::vector<Core::Entity>{{3.523, 3.812, 2}, {1.834, 8.765, 0}, {5.323, 5.365, 1}, {4.123, 10.265, 2}};
		// Core::Player player{3.456, 2.345, 1.523, M_PI / 3.f};
		// Core::Map map;
		// Core::Scene scene{map, player, entities};
		// scene.load_splash(Core::Splash{"assets/splash_zjvl.png", 3000});
		// current_scene = scene;
		// m_input.add_observer(&current_scene.player);
		// Core::TextureX splash_tex = Core::TextureX("assets/splash_zjvl.png", m_renderer);
		// auto splash = std::make_shared<SplashScene>(splash_tex, 5000);
		auto splash_scene = std::make_shared<SplashScene>();
		splash_scene->texture = std::make_shared<Core::TextureX>("assets/splash_zjvl.png", m_renderer);
		splash_scene->display_ms = 1000;

		auto game_scene = std::make_shared<GameScene>();
		scene_manager.change_to(game_scene);

		Core::Timer timer;
		int framecount = 0;
		std::uint32_t dt_start_time = timer.get_time();
		std::uint32_t dt_end_time = 0;
		while (m_running)
		{
			update();
			render();

			framecount++;
			if (timer.get_duration() >= 1000)
			{
				m_fps = framecount;
				// std::cout << "FPS: " << m_fps << std::endl;
				framecount = 0;
				timer.reset_duration();
			}

			// Calculate Delta Time
			dt_end_time = timer.get_time();
			m_dt = dt_end_time - dt_start_time;
			dt_start_time = dt_end_time;
		}
		// m_input.remove_observer(&current_scene.player);

		cleanup();
		return 0;
	}

	bool App::init()
	{

		// m_renderer.init();

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		{
			std::cout << "Failed to initialize SDL. SDL ERROR: " << SDL_GetError() << std::endl;
			return false;
		}

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			std::cout << "Failed to initialize SDL_image. SDL ERROR: " << SDL_GetError() << std::endl;
			return false;
		}

		// Initialize SDL window
		m_window = SDL_CreateWindow(
		    m_app_name,
		    SDL_WINDOWPOS_CENTERED,
		    SDL_WINDOWPOS_CENTERED,
		    m_win_w,
		    m_win_h,
		    SDL_WINDOW_SHOWN);

		if (m_window == nullptr)
		{
			std::cout << "Failed to create SDL Window. SDL_ERROR: " << SDL_GetError() << std::endl;
			return false;
		}

		// Initialize SDL renderer
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (m_renderer == nullptr)
		{
			std::cout << "Failed to create SDL Renderer. SDL_ERROR: " << SDL_GetError() << std::endl;
			return false;
		}
		SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_UpdateWindowSurface(m_window);

		m_input.init();
		scene_manager.init(m_renderer);
		return true;

		// m_window.add_observer(this);
		// m_window.input_manager.add_observer(this);
		// return m_window.init();
	}

	// This is where any post processing gameplay updates may happen.
	// Note that this is called after the event handlers have been called,
	// and is the final step before updates to do any kind of processing.
	void App::update()
	{
		// m_window.update();
		while (SDL_PollEvent(&m_event))
		{
			if (m_event.type == SDL_QUIT)
			{
				Core::WindowCloseEvent e;
				notify(e);
				m_running = false;
				break;
			}
			m_input.on_event(m_event);
		}
		// We only need to update mouse once per tick
		m_input.update_mouse();
		scene_manager.update(m_dt);
	}

	void App::render()
	{

		SDL_RenderClear(m_renderer);
		scene_manager.render();
		SDL_RenderPresent(m_renderer);
		// m_renderer.set_scene(current_scene);
		// Core::FrameBuffer *framebuffer = m_renderer.render();
		// m_window.draw(static_cast<void *>(framebuffer->img.data()), framebuffer->w * 4);
	}

	void App::cleanup()
	{
		// m_renderer.cleanup();
		// m_window.remove_observer(this);
		// m_window.cleanup();
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		IMG_Quit();
		SDL_Quit();
	}

	// // This is where all events are handled at the application level.
	// // For Scene, Entity specific events, use their own respective member functions.
	// void App::on_notify(Core::Event &e)
	// {
	// 	switch (e.get_type())
	// 	{
	// 	case Core::EventType::WINDOW_QUIT:
	// 		m_running = false;
	// 		break;
	// 	}
	// }
}