#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "splash.h"

class Renderer
{
public:
	Renderer();
	Renderer(const char *title, size_t win_w, size_t win_h);
	bool init();
	bool render();
	void cleanup();
	bool render_splash(const Splash &splash_image);
	void load_splash(Splash splash_image);

private:
	const char *title;
	size_t win_w, win_h;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;

	SDL_Texture *splash_texture;
	SDL_Surface *splash_surface;
};

#endif