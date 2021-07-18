#ifndef ZJVL_CORE_EVENT_LISTENER_H
#define ZJVL_CORE_EVENT_LISTENER_H

#include "event.h"

namespace ZJVL
{
	namespace Core
	{
		class EventListener
		{
		public:
			virtual ~EventListener();
			virtual void on_notify(Event e) = 0;
		};
	}
}

#endif