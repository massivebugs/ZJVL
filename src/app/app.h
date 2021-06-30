#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class App
{
public:
	App(const char* app_name, size_t win_w, size_t win_h);
	int on_execute();

	bool on_init();

	void on_event(const SDL_Event &event);

	void on_loop();

	void on_render();

	void on_cleanup();

	bool add_splash_image(const char *path, int seconds);

private:
	bool running;
	const char *app_name;
	size_t win_w, win_h;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	// SDL_Texture *splash_texture;
	int mouse_x, mouse_y;

	// std::vector<const char *> splash_images;
	// Map map;
	// std::vector<Sprite> sprites;
	// Player player;
	// Texture wall_tex;
	// Texture sprites_tex;
};

#endif