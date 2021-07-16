#ifndef ZJVL_WINDOW_H
#define ZJVL_WINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderer/framebuffer.h"
#include "scene/splash.h"

namespace ZJVL
{
	class Window
	{
	public:
		Window(const char *name, int w, int h);
		bool init();
		bool get_event();
		bool draw(FrameBuffer* framebuffer);
		bool draw_splash(const Splash &splash_image);
		void cleanup();
		void get_mouse();
		int mouse_x, mouse_y;

	private:
		const char *m_name;
		int m_width, m_height;

		SDL_Window *m_window;
		SDL_Renderer *m_renderer;
		SDL_Texture *m_texture;
	};

}
#endif
