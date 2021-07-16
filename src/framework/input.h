#ifndef ZJVL_INPUT_H
#define ZJVL_INPUT_H

#include <SDL2/SDL.h>

namespace ZJVL
{
	class Input
	{
	public:
		Input();
		~Input();
		void on_event(const SDL_Event &event);
		virtual void on_exit();
		virtual void on_keydown();
	};
}

#endif