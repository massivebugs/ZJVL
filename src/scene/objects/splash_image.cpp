#include "all.h"
#include <SDL2/SDL.h>
#include "core/app.h"
#include "scene/scene.h"
#include "splash_image.h"

namespace ZJVL
{
  SplashImage::SplashImage(const std::string &img_file, std::uint32_t display_ms, const std::string &next_scene_id)
      : display_ms(display_ms),
        next_scene_id(next_scene_id),
        image(img_file){};

  bool SplashImage::create(const Scene &scene)
  {
    return true;
  };
  void SplashImage::update(const Scene &scene, std::uint32_t dt)
  {
    // Switch to next scene on timeout
    if (scene.shown_ms >= display_ms && next_scene_id.empty() == false)
      App::instance()->scene_manager.switch_to(next_scene_id);
  };

  void SplashImage::render(const Scene &scene, SDL_Renderer *renderer)
  {
    SDL_RenderCopy(renderer, image.data, NULL, NULL);
  };

  void SplashImage::destroy(){

  };

  void SplashImage::on_notify(Event &e){

  };
}