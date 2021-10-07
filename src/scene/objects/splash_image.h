#ifndef ZJVL_SCENE_SPLASH_IMAGE_H
#define ZJVL_SCENE_SPLASH_IMAGE_H

#include "all.h"
#include <SDL2/SDL.h>
#include "scene/scene.h"
#include "asset/texture.h"
#include "scene/game_object.h"

namespace ZJVL
{
  class SplashImage : public GameObject
  {
  public:
    SplashImage(const std::string &img_file, std::uint32_t display_ms = 0, const std::string &next_scene_id = "");

    bool create(const Scene &scene) override;
    void update(const Scene &scene, std::uint32_t dt) override;
    void render(const Scene &scene, SDL_Renderer *renderer) override;
    void destroy() override;
    void on_notify(Event &e) override;

  private:
    Texture image;
    std::uint32_t display_ms;
    std::string next_scene_id;
  };
}

#endif