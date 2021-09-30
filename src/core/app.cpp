#include "all.h"
#include "app.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "event/window_event.h"

namespace ZJVL
{
	App *App::instance()
	{
		static App *instance = new App();
		return instance;
	}

	App::App()
	    : m_dt(0),
	      m_fps(0),
	      m_running(false),
	      m_window(nullptr),
	      renderer(nullptr)
	{
		std::cout << "Creating App instance" << std::endl;
	}

	bool App::init(const std::string &name, int window_w, int window_h)
	{
		this->name = name;
		this->window_w = window_w;
		this->window_h = window_h;

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		{
			std::cout << "Failed to initialize SDL. SDL ERROR: " << SDL_GetError() << std::endl;
			return false;
		}

		if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG)))
		{
			std::cout << "Failed to initialize SDL_image. SDL ERROR: " << SDL_GetError() << std::endl;
			return false;
		}

		m_window = SDL_CreateWindow(
		    name.c_str(),
		    SDL_WINDOWPOS_CENTERED,
		    SDL_WINDOWPOS_CENTERED,
		    window_w,
		    window_h,
		    0 & SDL_WINDOW_FULLSCREEN_DESKTOP);
		// TODO: Create settings for full screens

		if (m_window == nullptr)
		{
			std::cout << "Failed to create SDL Window. SDL_ERROR: " << SDL_GetError() << std::endl;
			return false;
		}

		renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr)
		{
			std::cout << "Failed to create SDL Renderer. SDL_ERROR: " << SDL_GetError() << std::endl;
			return false;
		}
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_UpdateWindowSurface(m_window);

		input_system.init();
		scene_manager.init(renderer, window_w, window_h);

		return true;
	}

	// This is the main execution loop,
	// where all of the game loop functionalities
	// are tied together.
	int App::run()
	{
		// Make sure we don't duplicate calls
		if (m_running)
			return 0;
		m_running = true;

		Timer timer;
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
				std::cout << "FPS: " << m_fps << std::endl;
				framecount = 0;
				timer.reset_duration();
			}

			// Calculate Delta time
			dt_end_time = timer.get_time();
			m_dt = dt_end_time - dt_start_time;
			dt_start_time = dt_end_time;
		}

		cleanup();
		return 0;
	}

	void App::update()
	{
		// Process events
		while (SDL_PollEvent(&m_event))
		{
			if (m_event.type == SDL_QUIT)
			{
				WindowCloseEvent e;
				notify(e);
				m_running = false;
				break;
			}
			input_system.on_event(m_event);
		}

		// Update other systems after application events have been processed
		input_system.update_mouse();
		scene_manager.update(m_dt);
	}

	void App::render()
	{
		SDL_RenderClear(renderer);
		scene_manager.render();
		SDL_RenderPresent(renderer);
	}

	void App::cleanup()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(m_window);
		IMG_Quit();
		SDL_Quit();
	}
}