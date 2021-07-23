#include <SDL2/SDL.h>
#include <iostream>
#include "timer.h"

namespace ZJVL
{
	namespace Framework
	{
		Timer::Timer()
		{
			reset_duration();
		};

		uint32_t Timer::get_time() {
			return SDL_GetTicks();
		}

		uint32_t Timer::get_duration()
		{
			return get_time() - m_duration_start;
		}

		void Timer::reset_duration()
		{
			m_duration_start = get_time();
		}
	}
}