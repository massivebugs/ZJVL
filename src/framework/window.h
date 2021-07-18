#ifndef ZJVL_FRAMEWORK_WINDOW_H
#define ZJVL_FRAMEWORK_WINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
#include <memory>
#include "core/event/event.h"

namespace ZJVL
{
	namespace Framework
	{
		class Window
		{
		public:
			Window(const char *name, int w, int h);
			bool init();
			bool draw(void* buffer, int row_bytes);

			bool flash_image(const char* img_path, uint32_t ms);
			void cleanup();
			void get_mouse();
			int mouse_x, mouse_y;
			bool poll_event(std::shared_ptr<Core::Event> e);

		private:
			const char *m_name;
			int m_width, m_height;

			SDL_Window *m_window;
			SDL_Renderer *m_renderer;
			SDL_Texture *m_texture;
			SDL_Event m_event;

		};

	}
}
#endif
