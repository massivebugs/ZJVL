#include "all.h"
#include "event.h"
#include "window_event.h"

namespace ZJVL
{
    EventType WindowCloseEvent::get_type() const
    {
        return EventType::WINDOW_QUIT;
    }
}