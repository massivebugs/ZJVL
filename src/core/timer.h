#ifndef ZJVL_CORE_TIMER_H
#define ZJVL_CORE_TIMER_H

#include "all.h"
#include <SDL2/SDL.h>

namespace ZJVL
{
	class Timer
	{
	public:
		Timer()
		{
			reset_duration();
		};

		std::uint32_t get_time()
		{
			return SDL_GetTicks();
		};

		std::uint32_t get_duration()
		{

			return get_time() - m_duration_start;
		};

		void reset_duration()
		{
			m_duration_start = get_time();
		};

	private:
		std::uint32_t m_duration_start;
	};
}

#endif