#include "all.h"
#include "mouse_event.h"

namespace ZJVL
{
    MouseMoveEvent::MouseMoveEvent(int x, int y) : x(x), y(y){};
    EventType MouseMoveEvent::get_type() const
    {
        return EventType::MOUSEMOVE;
    }
}