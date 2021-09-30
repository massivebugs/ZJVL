#ifndef ZJVL_CORE_INPUT_H
#define ZJVL_CORE_INPUT_H

#include "all.h"
#include <SDL2/SDL.h>
#include "event/subject.h"
#include "event/key_event.h"
#include "event/mouse_event.h"

namespace ZJVL
{
	class InputSystem : public Subject
	{
	public:
		InputSystem();

		void init();

		void on_event(SDL_Event &e);

		void update_mouse();

	private:
		int m_mouse_x, m_mouse_y;
		std::unordered_map<SDL_Keycode, Key> m_keymap;
	};
}

#endif