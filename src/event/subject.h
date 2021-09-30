#ifndef ZJVL_EVENT_SUBJECT_CPP
#define ZJVL_EVENT_SUBJECT_CPP

#include "all.h"
#include "observer.h"

namespace ZJVL
{
	class Subject
	{
	public:
		virtual ~Subject() = default;
		void add_observer(Observer *observer);

		void remove_observer(Observer *observer);

	protected:
		std::vector<Observer *> m_observers;
		void notify(Event &event);
	};
}
#endif