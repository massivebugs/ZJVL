#ifndef ZJVL_TIMER_H
#define ZJVL_TIMER_H

namespace ZJVL {
	class Timer {
		public:
			Timer();
			void reset();
			uint32_t get_duration();
		
		private:
			uint32_t m_start_time;
	};
}

#endif