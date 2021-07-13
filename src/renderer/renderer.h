#ifndef ZJVL_RENDERER_H
#define ZJVL_RENDERER_H

#include <vector>
#include "scene/splash.h"
#include "scene/map.h"
#include "framebuffer.h"
#include "textures.h"
#include "scene/entity.h"
#include "scene/scene.h"

namespace ZJVL
{
	class Renderer
	{
	public:
		Renderer(int w, int h);

		bool init();
		void set_scene(Scene scene);
		FrameBuffer* render();
		void cleanup();

	private:
		std::size_t rect_w;
		std::size_t rect_h;

		Scene scene;
		FrameBuffer framebuffer;
		Texture wall_tex = Texture("assets/walltext.png");
		Texture entities_tex = Texture("assets/monsters.png");
		std::vector<float> depth_buffer;

		void draw_map();
		void draw_entity(Entity &entity);
		void cast_ray();

		void clear(const uint32_t color);
		void set_pixel(const size_t x, const size_t y, const uint32_t color);
		void draw_rectangle(const size_t x, const size_t y, const size_t w, const size_t h, const uint32_t color);
		bool is_transparent_pixel(const uint32_t &color);
	};
}

#endif