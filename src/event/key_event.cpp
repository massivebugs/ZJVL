#include "all.h"
#include "key_event.h"

namespace ZJVL
{
    KeyDownEvent::KeyDownEvent(Key key) : m_key(key){};
    EventType KeyDownEvent::get_type() const
    {
        return EventType::KEYDOWN;
    }

    Key KeyDownEvent::get_key() const
    {
        return m_key;
    }
}