#include <SDL2/SDL.h>
#include <iostream>
#include "timer.h"

namespace ZJVL
{
	Timer::Timer()
	{
		reset();
	};

	void Timer::reset()
	{
		m_start_time = SDL_GetTicks();
		std::cout << "Timer reset" << std::endl;
	}

	uint32_t Timer::get_duration()
	{
		return SDL_GetTicks() - m_start_time;
	}
}