#ifndef ZJVL_CORE_EVENT_WINDOW_EVENT_H
#define ZJVL_CORE_EVENT_WINDOW_EVENT_H
#include "../event.h"

namespace ZJVL
{
	namespace Event
	{
		class WindowEvent: public Event {
		};

		class WindowCloseEvent: public WindowEvent {
			EventType get_type() const override
			{
				return EventType::WINDOW_QUIT;
			}
		};
	}
}
#endif