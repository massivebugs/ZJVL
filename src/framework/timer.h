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
			void reset();
			uint32_t get_duration();

		private:
			uint32_t m_start_time;
		};
	}
}

#endif