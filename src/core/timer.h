#ifndef ZJVL_CORE_TIMER_H
#define ZJVL_CORE_TIMER_H

#include "all.h"

namespace ZJVL
{
	class Timer
	{
	public:
		Timer();

		std::uint32_t get_time();

		std::uint32_t get_duration();

		void reset_duration();

	private:
		std::uint32_t m_duration_start;
	};
}

#endif