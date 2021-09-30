#ifndef ZJVL_EVENT_WINDOW_EVENT_H
#define ZJVL_EVENT_WINDOW_EVENT_H
#include "event.h"

namespace ZJVL
{
	class WindowEvent : public Event
	{
	};

	class WindowCloseEvent : public WindowEvent
	{
		EventType get_type() const override;
	};
}
#endif