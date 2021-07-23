#ifndef ZJVL_FRAMEWORK_TIMER_H
#define ZJVL_FRAMEWORK_TIMER_H

#include <cstdint>

namespace ZJVL
{
	namespace Framework
	{
		class Timer
		{
		public:
			Timer();
			uint32_t get_time();
			uint32_t get_duration();
			void reset_duration();

		private:
			uint32_t m_duration_start;
		};
	}
}

#endif