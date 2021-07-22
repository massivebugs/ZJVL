#include "event_system.h"
#include "event.h"

namespace ZJVL
{
	namespace Core
	{
		EventSystem::EventSystem()
		{
			// // If necessary, reserve later to reduce copying
			// m_observers.reserve(10);
		}

		void EventSystem::add_observer(Observer &observer) {
			m_observers.push_back(observer);
		}

		void EventSystem::notify(Event &event) {
			for (Observer& observer: m_observers) {
				observer.on_notify(event);
			};
		}
	}
}