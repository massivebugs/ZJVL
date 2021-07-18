#ifndef ZJVL_CORE_EVENT_WINDOW_EVENT_H
#define ZJVL_CORE_EVENT_WINDOW_EVENT_H

#include "event.h"

namespace ZJVL
{
	namespace Core
	{
		class WindowEvent : public Event
		{
		public:
			WindowEvent(EventType type = EventType::WINDOW) : Event(type){};
		};

		class WindowQuitEvent : public WindowEvent
		{
		public:
			WindowQuitEvent() : WindowEvent(EventType::QUIT) {};
		};
	}
}
#endif