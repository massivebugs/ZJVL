#ifndef ZJVL_EVENT_MOUSE_EVENT_H
#define ZJVL_EVENT_MOUSE_EVENT_H
#include "event.h"

namespace ZJVL
{
	class MouseEvent : public Event
	{
	};

	class MouseMoveEvent : public MouseEvent
	{
	public:
		MouseMoveEvent(int x, int y);
		EventType get_type() const override;
		const int x;
		const int y;
	};
}
#endif