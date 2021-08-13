#ifndef ZJVL__EVENT_OBSERVER_H
#define ZJVL__EVENT_OBSERVER_H

#include "event.h"

namespace ZJVL
{
	namespace Event
	{
		class Observer
		{
		public:
			virtual ~Observer(){};
			virtual void on_notify(Event &e) = 0;
		};
	}
}

#endif