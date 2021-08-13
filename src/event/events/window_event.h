#ifndef ZJVL__EVENT_WINDOW_EVENT_H
#define ZJVL__EVENT_WINDOW_EVENT_H
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