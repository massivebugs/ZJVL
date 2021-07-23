#ifndef ZJVL_CORE_EVENT_EVENT_H
#define ZJVL_CORE_EVENT_EVENT_H

namespace ZJVL
{
	namespace Core
	{
		enum class EventType
		{
			APPLICATION,
			WINDOW_QUIT,
			KEYDOWN,
		};

		class Event
		{
		public:
			virtual ~Event(){};

			virtual EventType get_type() const = 0;

			bool should_be_handled() const
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