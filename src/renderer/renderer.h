#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "splash.h"
#include "map.h"
#include "framebuffer.h"
#include "textures.h"
#include "entity/entity.h"

class Renderer
{
public:
	Renderer();
	Renderer(const char *title, size_t win_w, size_t win_h);

	bool init();
	bool render(Entity &player, std::vector<Entity> &entities);
	void cleanup();

	bool render_splash(const Splash &splash_image);
	void load_splash(Splash splash_image);


private:
	const char *title;
	std::size_t win_w, win_h;
	std::size_t rect_w;
	std::size_t rect_h;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;

	SDL_Texture *splash_texture;
	SDL_Surface *splash_surface;

	FrameBuffer framebuffer;
	Map map;
	Texture wall_tex = Texture("assets/walltext.png");
	Texture entities_tex = Texture("assets/monsters.png");
	std::vector<float> depth_buffer;

	void draw_map();
	void draw_entity(Entity &player, Entity &entity);
	void cast_ray(Entity &player);
};

#endif