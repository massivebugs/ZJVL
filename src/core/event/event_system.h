#ifndef ZJVL_CORE_EVENT_EVENT_TYPE_H
#define ZJVL_CORE_EVENT_EVENT_TYPE_H
#include <vector>
#include "event.h"
#include "observer.h"

namespace ZJVL
{
	namespace Core
	{
		class EventSystem
		{
		public:
			EventSystem();

			static void add_observer(Observer &observer);

		private:
			static std::vector<Observer> m_observers;
			static void notify(Event &event);
		}
	};
}
#endif