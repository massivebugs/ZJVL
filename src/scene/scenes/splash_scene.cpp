#include "all.h"
#include <SDL2/SDL.h>
#include "core/app.h"
#include "scene/scene.h"
#include "splash_scene.h"
#include "asset/texture.h"

namespace ZJVL
{
    SplashScene::SplashScene(const std::string &img_file, std::uint32_t display_ms, const std::string &next_scene_id)
        : display_ms(display_ms),
          next_scene_id(next_scene_id),
          splash_image(img_file)
    {
        std::cout << "Creating Splash Scene" << std::endl;
    }

    void SplashScene::load()
    {
        std::cout << "Loading Splash Scene" << std::endl;
        m_shown_ms = 0;
    }

    void SplashScene::unload()
    {
        std::cout << "Unloading Splash Scene" << std::endl;
    }

    void SplashScene::update(std::uint32_t dt)
    {
        m_shown_ms += dt;

        fade(dt);

        // Switch to next scene on timeout
        if (m_shown_ms >= display_ms && next_scene_id.empty() == false)
            App::instance()->scene_manager.show(next_scene_id);
    }

    void SplashScene::render(SDL_Renderer *renderer)
    {
        SDL_RenderCopy(renderer, splash_image.data, NULL, NULL);
    }

    void SplashScene::set_fading(std::uint32_t in_ms, std::uint32_t out_ms)
    {
        texture.set_blending();
        texture.set_alpha(0);

        m_fade = true;
        m_fade_in_ms = in_ms;
        m_fade_out_ms = out_ms;
    }

    void SplashScene::fade(std::uint32_t dt)
    {
        if (m_fade)
        {
            // Fade in
            if (m_shown_ms < m_fade_in_ms)
            {
                texture.set_alpha(255 * ((float)m_shown_ms / m_fade_in_ms));
            }

            // Fade out
            else if (display_ms - m_shown_ms < m_fade_out_ms)
            {
                texture.set_alpha(255 * ((float)(display_ms - m_shown_ms) / m_fade_out_ms));
            }

            else
            {
                texture.set_alpha(m_shown_ms <= display_ms ? 255 : 0);
            }
        }
    }
}