#ifndef ZJVL_FRAMEWORK_TIMER_H
#define ZJVL_FRAMEWORK_TIMER_H

#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>

namespace ZJVL
{
	namespace Framework
	{
		class Timer
		{
		public:
			Timer()
			{
				reset_duration();
			};
			uint32_t get_time()
			{
				return SDL_GetTicks();
			};
			uint32_t get_duration()
			{

				return get_time() - m_duration_start;
			};
			void reset_duration()
			{

				m_duration_start = get_time();
			};

		private:
			uint32_t m_duration_start;
		};
	}
}

#endif