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
    }

    void SplashScene::unload()
    {
        std::cout << "Unloading Splash Scene" << std::endl;
    }

    void SplashScene::update(std::uint32_t dt)
    {
        // Switch to next scene on timeout
        if (m_shown_ms >= display_ms && next_scene_id.empty() == false)
            App::instance()->scene_manager.switch_to(next_scene_id);
    }

    void SplashScene::render(SDL_Renderer *renderer)
    {
        SDL_RenderCopy(renderer, splash_image.data, NULL, NULL);
    }

}