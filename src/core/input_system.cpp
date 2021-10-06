#include "all.h"
#include "input_system.h"
#include "event/key_event.h"
#include "event/mouse_event.h"

namespace ZJVL
{
    InputSystem::InputSystem() : m_keymap{
                        {SDLK_KP_ENTER, Key::ENTER},
                        {SDLK_ESCAPE, Key::ESC},
                        {SDLK_w, Key::W},
                        {SDLK_a, Key::A},
                        {SDLK_s, Key::S},
                        {SDLK_d, Key::D},
                        {SDLK_m, Key::M}
                    } {};

    void InputSystem::init()
    {
        // Motion is limited to bounds of screen
        SDL_SetRelativeMouseMode(SDL_TRUE);
    };

    void InputSystem::on_event(SDL_Event &e)
    {
        if (e.type == SDL_KEYDOWN)
        {
            SDL_Keycode keycode = e.key.keysym.sym;
            if (m_keymap.find(keycode) != m_keymap.end())
            {
                KeyDownEvent e(m_keymap[keycode]);
                notify(e);
            }
        }
    };

    void InputSystem::update_mouse()
    {
        SDL_GetRelativeMouseState(&m_mouse_x, &m_mouse_y);
        if (m_mouse_x != 0 || m_mouse_y != 0)
        {
            MouseMoveEvent e(m_mouse_x, m_mouse_y);
            notify(e);
        }
    }
}