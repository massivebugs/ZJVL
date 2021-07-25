#ifndef ZJVL_CORE_EVENT_MOUSE_EVENT_H
#define ZJVL_CORE_EVENT_MOUSE_EVENT_H
#include "../event.h"

namespace ZJVL
{
	namespace Core
	{
		class MouseEvent : public Event
		{
		};

		class MouseMoveEvent : public MouseEvent
		{
		public:
			MouseMoveEvent(int x, int y) : mouse_x(x), mouse_y(y){};
			EventType get_type() const override
			{
				return EventType::MOUSEMOVE;
			}
			const int mouse_x;
			const int mouse_y;
		};
	}
}
#endif