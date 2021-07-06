#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderer.h"
#include "splash.h"

Renderer::Renderer()
{
	title = "Game";
	win_w = 1920;
	win_h = 1080;

	window = nullptr;
	renderer = nullptr;
	texture = nullptr;
}

Renderer::Renderer(const char *title, size_t win_w, size_t win_h)
{
	this->title = title;
	this->win_w = win_w;
	this->win_h = win_h;

	window = nullptr;
	renderer = nullptr;
	texture = nullptr;
}

bool Renderer::init()
{
	// Initialize SDL window
	window = SDL_CreateWindow(
	    title,
	    SDL_WINDOWPOS_CENTERED,
	    SDL_WINDOWPOS_CENTERED,
	    win_w,
	    win_h,
	    SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "Failed to create SDL Window. SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}

	// Initialize SDL renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_UpdateWindowSurface(window);

	return true;
}

void Renderer::cleanup()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

bool Renderer::render_splash(const Splash &splash_image)
{
	std::cout << "Rendering splash..." << std::endl;

	// Display splashes here
	splash_surface = IMG_Load(splash_image.img_path);
	if (splash_surface == nullptr)
	{
		std::cout << "Failed to load splash image . SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}
	splash_texture = SDL_CreateTextureFromSurface(renderer, splash_surface);
	if (splash_texture == nullptr)
	{
		std::cout << "Failed to load splash image . SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, splash_texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_Delay(splash_image.display_ms);

	SDL_FreeSurface(splash_surface);
	SDL_DestroyTexture(splash_texture);
	return true;
}