#include "all.h"
#include "subject.h"
#include "observer.h"

namespace ZJVL
{

    void Subject::add_observer(Observer *observer)
    {
        // TODO: Check for duplicates
        m_observers.push_back(observer);
    }

    void Subject::remove_observer(Observer *observer)
    {
        auto idx = std::find(m_observers.begin(), m_observers.end(), observer);
        if (idx != m_observers.end())
        {
            m_observers.erase(idx);
        }
    }

    void Subject::notify(Event &event)
    {
        for (Observer *observer : m_observers)
        {
            if (event.should_be_handled() == false)
                break;

            observer->on_notify(event);
        }
    }
}