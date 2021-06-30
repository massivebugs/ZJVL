#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "app.h"

App::App(const char *app_name, size_t win_w, size_t win_h)
{
	this->app_name = app_name;
	this->win_w = win_w;
	this->win_h = win_h;

	window = nullptr;
	renderer = nullptr;
	texture = nullptr;

	running = true;
}

int App::on_execute()
{
	if (on_init() == false)
	{
		return -1;
	}

	// Load splash textures here

	// Setup game here 

	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			on_event(event);
		};

		on_loop();
		on_render();
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

	// Initialize SDL window
	window = SDL_CreateWindow(
	    app_name,		    // window title
	    SDL_WINDOWPOS_CENTERED, // initial x position
	    SDL_WINDOWPOS_CENTERED, // initial y position
	    win_w,
	    win_h,
	    SDL_WINDOW_SHOWN	    // flags - see below
	);

	if (window == nullptr)
	{
		std::cout << "Failed to create SDL Window. SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}

	// Initialize SDL renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_UpdateWindowSurface(window);

	// Additional SDL configurations
	SDL_SetRelativeMouseMode(SDL_TRUE);

	return true;
}

void App::on_event(const SDL_Event &event) {}

void App::on_loop() {}

void App::on_render() {}

void App::on_cleanup()
{
	// SDL Cleanup
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

// // TODO: for test purposes
// int main(int argc, char *argv[])
// {
// 	return App("Test game", 1024, 512).on_execute();
// }