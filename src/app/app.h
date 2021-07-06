#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "renderer/renderer.h"

class App
{
public:
	App(const char *app_name, size_t win_w, size_t win_h);
	void load_splash(Splash splash_image);
	int run();

private:
	Renderer renderer;

	bool running;
	const char *app_name;
	std::vector<Splash> splash_images;

	int mouse_x, mouse_y;

	// Map map;
	// std::vector<Sprite> sprites;
	// Player player;
	// Texture wall_tex;
	// Texture sprites_tex;

	int on_execute();

	bool on_init();

	void on_event(const SDL_Event &event);

	void on_loop();

	void on_render();

	void on_cleanup();
};

#endif