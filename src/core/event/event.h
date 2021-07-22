#ifndef ZJVL_CORE_EVENT_EVENT_H
#define ZJVL_CORE_EVENT_EVENT_H

namespace ZJVL
{
	namespace Core
	{
		enum class EventType {
			APPLICATION,
			KEYDOWN,
		};

		class Event
		{
		public:
			Event() {
				m_type = EventType::APPLICATION;
			}

			Event(EventType type) {
				m_type = type;
			};

			virtual ~Event(){};

			virtual EventType get_type();

			bool should_be_handled()
			{
				return m_propagate;
			};

			void stop_propagation()
			{
				m_propagate = false;
			};

		protected:
			EventType m_type;
			bool m_propagate = true;
		};
	}
}

#endif