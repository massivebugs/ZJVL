#ifndef ZJVL_CORE_EVENT_EVENT_H
#define ZJVL_CORE_EVENT_EVENT_H

namespace ZJVL
{
	namespace Core
	{

		class Event
		{
		public:
			using EventType = const char *;

			virtual ~Event(){};

			virtual EventType get_type() = 0;

			bool should_be_handled()
			{
				return m_propagate;
			};

			void stop_propagation()
			{
				m_propagate = false;
			};

		protected:
			bool m_propagate = true;
		};
	}
}

#endif