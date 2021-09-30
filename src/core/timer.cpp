#include "all.h"
#include "timer.h"
#include <SDL2/SDL.h>

namespace ZJVL
{
    Timer::Timer()
    {
        reset_duration();
    };

    std::uint32_t Timer::get_time()
    {
        return SDL_GetTicks();
    };

    std::uint32_t Timer::get_duration()
    {

        return get_time() - m_duration_start;
    };

    void Timer::reset_duration()
    {
        m_duration_start = get_time();
    };
}