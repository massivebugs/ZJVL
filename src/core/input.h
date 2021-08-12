#ifndef ZJVL_CORE_INPUT_H
#define ZJVL_CORE_INPUT_H

#include "all.h"
#include <SDL2/SDL.h>
#include "event/subject.h"
#include "event/events/key_event.h"
#include "event/events/mouse_event.h"

namespace ZJVL
{
	namespace Core
	{
		class Input : public Event::Subject
		{
		public:
			Input() : m_keymap{
				      {SDLK_KP_ENTER, Event::Key::ENTER},
				      {SDLK_ESCAPE, Event::Key::ESC},
				      {SDLK_w, Event::Key::W},
				      {SDLK_a, Event::Key::A},
				      {SDLK_s, Event::Key::S},
				      {SDLK_d, Event::Key::D},
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
						Event::KeyDownEvent e(m_keymap[keycode]);
						notify(e);
					}
				}
			};

			void update_mouse()
			{
				SDL_GetRelativeMouseState(&m_mouse_x, &m_mouse_y);
				if (m_mouse_x != 0 || m_mouse_y != 0)
				{
					Event::MouseMoveEvent e(m_mouse_x, m_mouse_y);
					notify(e);
				}
			}

		private:
			int m_mouse_x, m_mouse_y;
			std::unordered_map<SDL_Keycode, Event::Key> m_keymap;
		};
	}
}

#endif