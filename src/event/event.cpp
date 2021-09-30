#include "all.h"
#include "event.h"

namespace ZJVL
{
    bool Event::should_be_handled() const
    {
        return m_propagate;
    };

    void Event::stop_propagation()
    {
        m_propagate = false;
    };
}