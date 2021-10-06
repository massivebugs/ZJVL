#include "all.h"
#include "subject.h"
#include "observer.h"

namespace ZJVL
{

    void Subject::add_observer(std::weak_ptr<Observer> observer)
    {
        // TODO: Check for duplicates
        m_observers.push_back(observer);
    }

    void Subject::remove_observer(std::weak_ptr<Observer> observer)
    {
        auto observer_equals = [&observer](const std::weak_ptr<Observer> &ptr)
        {
            return ptr.lock() == observer.lock();
        };

        auto idx = std::find_if(m_observers.begin(), m_observers.end(), observer_equals);

        if (idx != m_observers.end())
        {
            m_observers.erase(idx);
        }
    }

    void Subject::notify(Event &event)
    {
        for (std::weak_ptr<Observer> observer : m_observers)
        {
            if (event.should_be_handled() == false)
                break;

            if (!observer.expired())
                observer.lock()->on_notify(event);
            else
                remove_observer(observer);
        }
    }
}