#ifndef ZJVL_CORE_EVENT_OBSERVER_H
#define ZJVL_CORE_EVENT_OBSERVER_H

#include "event.h"

namespace ZJVL
{
	namespace Core
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