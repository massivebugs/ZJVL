#ifndef ZJVL_FRAMEWORK_WINDOW_H
#define ZJVL_FRAMEWORK_WINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include "core/event/subject.h"
#include <core/event/events/key_event.h>

namespace ZJVL
{
	namespace Framework
	{
		class Window : public Core::Subject
		{
		public:
			Window(const char *name, int w, int h);
			bool init();
			bool draw(void *buffer, int row_bytes);

			bool flash_image(const char *img_path, uint32_t ms);
			void cleanup();
			void poll_events();

		private:
			const char *m_name;
			int m_width, m_height;
			int m_mouse_x, m_mouse_y;

			SDL_Window *m_window;
			SDL_Renderer *m_renderer;
			SDL_Texture *m_texture;
			SDL_Event m_event;
			std::unordered_map<SDL_Keycode, Core::Key> m_keymap;
		};
	}
}
#endif
