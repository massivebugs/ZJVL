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
		void add_observer(std::weak_ptr<Observer> observer);

		void remove_observer(std::weak_ptr<Observer> observer);

	protected:
		std::vector<std::weak_ptr<Observer>> m_observers;
		void notify(Event &event);
	};
}
#endif