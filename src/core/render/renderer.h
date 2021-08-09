#ifndef ZJVL_CORE_RENDERER_H
#define ZJVL_CORE_RENDERER_H

#include "all.h"
#include "core/scene/scene.h"
#include "core/scene/splash.h"
#include "core/scene/map.h"
#include "framebuffer.h"
#include "textures.h"
#include "core/scene/entity.h"

namespace ZJVL
{
	namespace Core
	{
		class Renderer
		{
		public:
			Renderer();
			Renderer(int w, int h);

			bool init();
			void set_scene(Scene &scene);
			FrameBuffer *render();
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
			uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255);
			void unpack_color(const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a);
		};

	}
}

#endif