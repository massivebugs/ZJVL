#ifndef ZJVL_FRAMEWORK_INPUT_H
#define ZJVL_FRAMEWORK_INPUT_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include "core/event/subject.h"
#include "core/event/events/key_event.h"
#include "core/event/events/mouse_event.h"
namespace ZJVL
{
	namespace Framework
	{
		class Input : public Core::Subject
		{
		public:
			Input() : m_keymap{
				      {SDLK_KP_ENTER, Core::Key::ENTER},
				      {SDLK_ESCAPE, Core::Key::ESC},
				      {SDLK_w, Core::Key::W},
				      {SDLK_a, Core::Key::A},
				      {SDLK_s, Core::Key::S},
				      {SDLK_d, Core::Key::D},
				  } {};

			void init()
			{
				// Motion is limited to bounds of screen
				SDL_SetRelativeMouseMode(SDL_TRUE);
			};

			void on_event(SDL_Event &e)
			{
				if (e.type == SDL_KEYDOWN)
				{
					SDL_Keycode keycode = e.key.keysym.sym;
					if (m_keymap.find(keycode) != m_keymap.end())
					{
						Core::KeyDownEvent e(m_keymap[keycode]);
						notify(e);
					}
				}
			};

			void update_mouse()
			{
				SDL_GetRelativeMouseState(&m_mouse_x, &m_mouse_y);
				if (m_mouse_x != 0 || m_mouse_y != 0)
				{
					Core::MouseMoveEvent e(m_mouse_x, m_mouse_y);
					notify(e);
				}
			}

		private:
			int m_mouse_x, m_mouse_y;
			std::unordered_map<SDL_Keycode, Core::Key> m_keymap;
		};
	}
}

#endif