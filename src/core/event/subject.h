#ifndef ZJVL_CORE_EVENT_SUBJECT_CPP
#define ZJVL_CORE_EVENT_SUBJECT_CPP
#include <vector>
#include "observer.h"

namespace ZJVL
{
	namespace Core
	{
		class Subject
		{
		public:
			virtual ~Subject(){};
			std::size_t add_observer(Observer *observer)
			{
				m_observers.push_back(observer);
				return m_observers.size() - 1;
			}

			void remove_observer(std::size_t pos)
			{
				m_observers.erase(m_observers.begin() + pos);
			}

		protected:
			std::vector<Observer *> m_observers;
			void notify(Event &event)
			{
				for (Observer *observer : m_observers)
				{
					if (event.should_be_handled() == false)
						break;

					observer->on_notify(event);
				}
			}
		};
	}
}
#endif