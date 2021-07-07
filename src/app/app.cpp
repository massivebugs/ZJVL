#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "app.h"
#include "renderer/renderer.h"
#include "entity/entity.h"

namespace Engine
{
	App::App(const char *app_name, size_t win_w, size_t win_h)
	{
		this->app_name = app_name;

		renderer = Renderer(app_name, win_w, win_h);

		running = true;
	}

	void App::load_splash(Splash splash_image)
	{
		splash_images.push_back(splash_image);
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
		for (Splash splash_image : splash_images)
		{
			renderer.render_splash(splash_image);
		};

		// Setup game here
		SDL_Event event;
		entities = std::vector<Entity>{{3.523, 3.812, NULL, NULL, 2}, {1.834, 8.765,NULL, NULL,  0}, {5.323, 5.365,NULL, NULL,  1}, {4.123, 10.265,NULL, NULL,  2}};
		player = Entity{3.456, 2.345, 1.523, M_PI / 3.};
		renderer.render(player, entities);

		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				on_event(event);
			};

			on_loop();
			on_render();
			renderer.render(player, entities);
		}

		on_cleanup();
		return 0;
	}

	bool App::on_init()
	{
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

		// Additional SDL configurations
		SDL_SetRelativeMouseMode(SDL_TRUE);

		return renderer.init();
	}

	void App::on_event(const SDL_Event &event)
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
	}

	void App::on_loop()
	{

		SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
		player.angle += mouse_x * M_PI / 360;
	}

	void App::on_render() {}

	void App::on_cleanup()
	{
		// SDL Cleanup
		renderer.cleanup();
		IMG_Quit();
		SDL_Quit();
	}
}