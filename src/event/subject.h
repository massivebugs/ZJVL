#ifndef ZJVL_EVENT_SUBJECT_CPP
#define ZJVL_EVENT_SUBJECT_CPP

#include "all.h"
#include "observer.h"

namespace ZJVL
{
	namespace Event
	{
		class Subject
		{
		public:
			virtual ~Subject(){};
			void add_observer(Observer *observer)
			{
				// TODO: Check for duplicates
				m_observers.push_back(observer);
			}

			void remove_observer(Observer *observer)
			{
				auto idx = std::find(m_observers.begin(), m_observers.end(), observer);
				if (idx != m_observers.end())
				{
					m_observers.erase(idx);
				}
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